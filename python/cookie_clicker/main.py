import argparse

parser = argparse.ArgumentParser(description='Cookie Clicker')
parser.add_argument('cps', type=float, help='Your current CPS')
parser.add_argument('--frenzy', default=False, action='store_true', help='You have Frenzy Cookie')

def calculateCPS(args):
    if args.frenzy:
        return args.cps / 7
    else:
        return args.cps

def calcLuckyFrenzyComboBank(cps):
    return cps * 7 * 900 / 0.15

def calcLuckyFrenzyComboCookieGain(cps):
    return cps * 7 * 900

if __name__ == "__main__":
    args = parser.parse_args()
    cps = calculateCPS(args)

    print(f'Frenzy/Lucky cookie gain: {calcLuckyFrenzyComboCookieGain(cps):_}')
    print(f'Frenzy/Lucky min bank: {calcLuckyFrenzyComboBank(cps):_}')
    
