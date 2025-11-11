#!/usr/bin/env python3
from collections import defaultdict, deque
import sys

EPS = 'ε'
ENDMARK = '$'

def tokenize_rhs(rhs):
    """Split a RHS like 'A B c' or 'aBc' into symbols.
       This implementation treats contiguous non-space characters as tokens.
       If your grammar uses multi-char terminals/non-terminals separated by spaces,
       this will still work if you input them space-separated."""
    # prefer space-separated tokens if present
    if ' ' in rhs.strip():
        tokens = [t for t in rhs.strip().split() if t]
    else:
        # fallback: take each char as token (useful for toy grammars like aB)
        tokens = [ch for ch in rhs.strip()] if rhs.strip() else []
    return tokens if tokens else [EPS]

def eliminate_left_recursion(prods):
    """Eliminate immediate left recursion for each nonterminal.
       Note: This handles only immediate left recursion per nonterminal (standard algorithm)."""
    new_prods = defaultdict(list)
    for A in list(prods.keys()):
        alpha = []
        beta = []
        for prod in prods[A]:
            if prod and prod[0] == A:
                # A -> A alpha  (left-recursive)
                # store alpha (prod without leading A)
                alpha.append(prod[1:] if len(prod) > 1 else [EPS])
            else:
                beta.append(prod)
        if not alpha:
            # no left recursion
            new_prods[A].extend(prods[A])
        else:
            A_prime = A + "'"
            # betas become beta A'
            for b in beta:
                # if b is epsilon, then just A' is appended
                if b == [EPS]:
                    new_prods[A].append([A_prime])
                else:
                    new_prods[A].append(b + [A_prime])
            # A' productions: alpha A' | ε
            for a in alpha:
                if a == [EPS]:
                    new_prods[A_prime].append([A_prime])  # degenerate; handle carefully
                else:
                    new_prods[A_prime].append(a + [A_prime])
            new_prods[A_prime].append([EPS])
    # remove any accidental productions like [A'] -> [A'] which could loop; keep minimal
    # (the standard algorithm should not produce such; leaving as-is)
    return new_prods

def compute_first(prods):
    """Compute FIRST sets. prods: dict NT -> list of productions (each prod is list of symbols)"""
    first = defaultdict(set)
    # initialize terminals: any symbol that is not a nonterminal (key in prods) and not EPS
    nonterminals = set(prods.keys())
    # initialize FIRST of terminals when encountered
    changed = True
    while changed:
        changed = False
        for A in prods:
            for prod in prods[A]:
                # empty production
                if prod == [EPS]:
                    if EPS not in first[A]:
                        first[A].add(EPS); changed = True
                    continue
                nullable_prefix = True
                for X in prod:
                    if X == EPS:
                        if EPS not in first[A]:
                            first[A].add(EPS); changed = True
                        nullable_prefix = False
                        break
                    if X not in nonterminals:
                        # X is terminal
                        if X not in first[A]:
                            first[A].add(X); changed = True
                        nullable_prefix = False
                        break
                    else:
                        # add FIRST(X) - {ε} to FIRST(A)
                        to_add = first[X] - {EPS}
                        if not to_add.issubset(first[A]):
                            first[A] |= to_add
                            changed = True
                        if EPS in first[X]:
                            # continue to next symbol
                            nullable_prefix = True
                        else:
                            nullable_prefix = False
                            break
                if nullable_prefix:
                    if EPS not in first[A]:
                        first[A].add(EPS); changed = True
    return first

def compute_follow(prods, firsts, start):
    """Compute FOLLOW sets. prods: dict NT->list of prods, firsts: map, start: start symbol"""
    nonterminals = set(prods.keys())
    follow = defaultdict(set)
    follow[start].add(ENDMARK)
    changed = True
    while changed:
        changed = False
        for A in prods:
            for prod in prods[A]:
                prod_len = len(prod)
                for i, B in enumerate(prod):
                    if B in nonterminals:
                        # compute FIRST(beta)
                        beta_first = set()
                        nullable = True
                        for X in prod[i+1:]:
                            if X == EPS:
                                nullable = True
                                break
                            if X in nonterminals:
                                beta_first |= (firsts[X] - {EPS})
                                if EPS in firsts[X]:
                                    nullable = True
                                    continue
                                else:
                                    nullable = False
                                    break
                            else:
                                beta_first.add(X)
                                nullable = False
                                break
                        # add FIRST(beta) - {ε} to FOLLOW(B)
                        before = len(follow[B])
                        follow[B] |= beta_first
                        if ENDMARK in follow[B] and ENDMARK not in follow[B]:
                            pass
                        if nullable:
                            # add FOLLOW(A) to FOLLOW(B)
                            follow[B] |= follow[A]
                        if len(follow[B]) != before:
                            changed = True
    # remove EPS if present in follows (shouldn't be)
    for k in follow:
        follow[k].discard(EPS)
    return follow

def construct_parse_table(prods, firsts, follows):
    table = defaultdict(dict)
    terminals = set()
    nonterminals = set(prods.keys())
    # collect terminals
    for nt in prods:
        for prod in prods[nt]:
            for symbol in prod:
                if symbol != EPS and symbol not in nonterminals:
                    terminals.add(symbol)
    terminals.add(ENDMARK)
    # build table
    for A in prods:
        for prod in prods[A]:
            # compute FIRST(alpha) for alpha = prod
            first_alpha = set()
            if prod == [EPS]:
                first_alpha.add(EPS)
            else:
                nullable = True
                for X in prod:
                    if X == EPS:
                        first_alpha.add(EPS)
                        nullable = True
                        break
                    if X not in nonterminals:
                        first_alpha.add(X)
                        nullable = False
                        break
                    else:
                        first_alpha |= (firsts[X] - {EPS})
                        if EPS in firsts[X]:
                            nullable = True
                            continue
                        else:
                            nullable = False
                            break
                if nullable:
                    first_alpha.add(EPS)
            # for every terminal t in FIRST(alpha) - {ε}, add A->alpha to table[A,t]
            prod_str = " ".join(prod) if prod != [EPS] else EPS
            for t in (first_alpha - {EPS}):
                table[A][t] = f"{A} -> {prod_str}"
            # if ε in FIRST(alpha), for every b in FOLLOW(A), add A->alpha to table[A,b]
            if EPS in first_alpha:
                for b in follows.get(A, set()):
                    table[A][b] = f"{A} -> {prod_str}"
    return table, terminals

# ---------- Print parse table neatly ----------
def print_parse_table(table, terminals):
    terminals = sorted(list(terminals))
    nts = sorted(table.keys())
    col_width = max(10, max((len(t) for t in terminals), default=1) + 4)
    # Header
    print("\nParse Table:")
    print("NT".ljust(10), end='')
    for t in terminals:
        print(t.center(col_width), end='')
    print()
    print("-" * (10 + col_width * len(terminals)))
    for nt in nts:
        print(nt.ljust(10), end='')
        for t in terminals:
            entry = table[nt].get(t, "")
            print(entry.center(col_width), end='')
        print()

# ---------- Main ----------
def main():
    try:
        n = int(input("Enter number of productions: ").strip())
    except Exception:
        print("Invalid number")
        return
    prods = defaultdict(list)
    for _ in range(n):
        line = input().strip()
        if not line:
            continue
        if '->' not in line:
            print("Invalid production format (expected A->B|C). Got:", line)
            return
        lhs, rhs = line.split("->", 1)
        lhs = lhs.strip()
        right_parts = rhs.split('|')
        for r in right_parts:
            tokens = tokenize_rhs(r.strip())
            prods[lhs].append(tokens)

    # Keep original for display before/after if needed
    # Eliminate left recursion
    prods = eliminate_left_recursion(prods)
    start = list(prods.keys())[0]

    # Compute FIRST and FOLLOW
    firsts = compute_first(prods)
    follows = compute_follow(prods, firsts, start)

    # Construct parse table using transformed productions
    parse_table, terminals = construct_parse_table(prods, firsts, follows)

    # Display results
    print("\nGrammar after eliminating left recursion:")
    for nt in prods:
        prods_str = [" ".join(p) if p != [EPS] else EPS for p in prods[nt]]
        print(f"{nt} -> {' | '.join(prods_str)}")

    print("\nFIRST sets:")
    for nt in sorted(firsts.keys()):
        print(f"FIRST({nt}) = {{ {', '.join(sorted(firsts[nt]))} }}")

    print("\nFOLLOW sets:")
    for nt in sorted(follows.keys()):
        print(f"FOLLOW({nt}) = {{ {', '.join(sorted(follows[nt]))} }}")

    print_parse_table(parse_table, terminals)

if __name__ == "__main__":
    main()
