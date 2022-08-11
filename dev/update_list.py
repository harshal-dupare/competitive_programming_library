import os

os.system("find my_lib/lib/ -name \"*.hpp\" > my_lib/lib/my_lib.txt")
os.system("find my_lib/tests/ -name \"test*.cpp\" > my_lib/tests/test_my_lib.txt")

my_lib = "my_lib/lib/my_lib.txt"
fl = open(my_lib,'r')
ls = fl.readlines()
fl.close()

test_my_lib = "my_lib/tests/test_my_lib.txt"
tfl = open(test_my_lib,'r')
tls = tfl.readlines()
tfl.close()

def getloclist(l):
    """
    Split the path to file split wrt '/'
    returns the list of split strings
    """
    return l.split('/')

def touch(path):
    """
    create a file name `path`
    """
    open(path, 'a').close()
    print("added:"+path)
    pass

def delfl(path):
    """
    delete the file name `path`
    """
    os.remove(path)
    print("removed:"+path)
    pass

def testfl(l):
    l = getloclist(l)
    l[1] = 'tests'
    l[len(l)-1] = 'test_' + os.path.splitext(l[len(l)-1])[0]+".cpp"
    tl = '/'.join(l)
    return tl

def codefl(l):
    l = getloclist(l)
    l[1] = 'lib'
    l[len(l)-1] = os.path.splitext(l[len(l)-1])[0][5:]+".hpp"
    tl = '/'.join(l)
    return tl

def includefl(l):
    ct  = "#include <" + l[:-1] + ">"
    l = getloclist(l)
    l[1] = 'include'
    l[len(l)-1] = os.path.splitext(l[len(l)-1])[0]
    tl = '/'.join(l)
    return tl, ct

for l in ls:
    tpl = testfl(l)
    if not os.path.exists(tpl):
        touch(os.path.join(*getloclist(tpl)))
    
    ifl,ict = includefl(l)
    print(ifl,ict)
    if not os.path.exists(ifl):
        fldrpt = '/'.join(getloclist(ifl)[:-1])
        if not os.path.exists(fldrpt):
            print(f"Path {fldrpt} doesn't exists making it")
            os.makedirs(fldrpt)
        ff = open(ifl,'w')
        ff.write(ict)
        ff.close()

# for l in tls:
#     cpl = codefl(l[0:-1])
#     if not os.path.exists(cpl):
#         delfl(l[7:-1])