import os

os.system("cd .. &&  find my_lib/lib/ -name \"*.hpp\" > my_lib/lib/my_lib.txt && cd my_lib")
os.system("cd .. && find my_lib/tests/ -name \"test*.cpp\" > my_lib/tests/test_my_lib.txt && cd my_lib")

my_lib = "my_lib.txt"
fl = open(my_lib,'r')
ls = fl.readlines()
fl.close()

test_my_lib = "test_my_lib.txt"
tfl = open(test_my_lib,'r')
tls = tfl.readlines()
tfl.close()

def getloclist(l):
    return l.split('/')

def touch(path):
    open(path, 'a').close()
    print("added:"+path)
    pass

def delfl(path):
    os.remove(path)
    print("removed:"+path)
    pass

def testfl(l):
    l = getloclist(l)
    tl = ''
    for i in range(1,len(l)-1):
        tl+=l[i]+'/'
    tl+='tests/test_'
    tl+=os.path.splitext(l[len(l)-1])[0]+".cpp"
    return tl

def codefl(l):
    l = getloclist(l)
    tl = ''
    for i in range(1,len(l)-2):
        tl+=l[i]+'/'
    tl+=os.path.splitext(l[len(l)-1])[0][5:]+".hpp"
    return tl

for l in ls:
    tpl = testfl(l[0:-1])
    if not os.path.exists(tpl):
        touch(os.path.join(*getloclist(tpl)))

for l in tls:
    cpl = codefl(l[0:-1])
    if not os.path.exists(cpl):
        delfl(l[7:-1])