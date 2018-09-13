from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO

    # Split a at new line
    linesA = a.split("\n")

    # Split b at new line
    linesB = b.split("\n")

    # Compare both a & b returning list of what is similar
    return set(linesA).intersection(linesB)


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO

    # Split sentences in a
    sentencesA = sent_tokenize(a)

    # Split sentences in b
    sentencesB = sent_tokenize(b)

    # Return similarites of a & b
    return set(sentencesA).intersection(sentencesB)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    substringsA = list()
    substringsB = list()

    # Split a from i to n length
    for i in range(len(a)):
        if len(a) == n:
            substringsA.append(a[i:i + n])
            break
        elif len(a) <= n:
            break
        elif len(a[i:i + n]) < n:
            break
        else:
            substringsA.append(a[i:i + n])
    # Split b from j to n length
    for j in range(len(b)):
        if len(b) == n:
            substringsB.append(b[j:j + n])
            break
        elif len(b) <= n:
            break
        elif len(b[j:j + n]) < n:
            break
        else:
            substringsB.append(b[j:j + n])

    # Return similar items of a & b
    return set(substringsA).intersection(substringsB)