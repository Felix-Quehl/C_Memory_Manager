import json
import sys


def checkCoverage(obj, minCov):
    insufficient = False
    for report in obj["data"]:
        total: dict = report["totals"]
        metrics = total.items()
        print('*'*50)
        print("\nCoverage:\n")
        for metric in metrics:
            name = metric[0].ljust(15)
            value = metric[1]["percent"]
            print(f"\t{name}\t:\t{value:.{2}f}%")
            if (value < minCov):
                insufficient = True
    print("\n"+'*'*50)
    return insufficient


if __name__ == "__main__":
    minCov = int(sys.argv[1])
    str = sys.stdin.read()
    obj = json.loads(str)
    insufficient = checkCoverage(obj, minCov)
    if (insufficient):
        print("Insufficient Coverage")
        exit(1)
    else:
        exit(0)
