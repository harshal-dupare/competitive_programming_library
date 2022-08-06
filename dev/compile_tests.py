import os
import subprocess

test_my_lib = "my_lib.txt"
out_file = "compile_result.txt"
tfl = open(test_my_lib,'r')
tls = tfl.readlines()
tfl.close()


# opf = open(out_file,'w')
# for l in tls:
#     l = l[0:-1]
#     opf.write("\n"+l+":\n"+80*'-'+"\n")
#     cmd = "g++ "+l[7:]
#     print(cmd)
#     try:
#         opc = subprocess.check_output(cmd,shell=True)
#         opc = opc.decode('utf-8')
#         print("PRINGINT|||||||:::: \n\n"+opc)
#         opf.write(opc)
#     except Exception, e:
#         opc = str(e.output)
#         print("PRINGINT|||||||:::: \n\n"+opc)
#         opf.write(opc)
#     # os.system(cmd)
#     opf.write("\n"+80*'-'+"\n")
# opf.close()

n = len(tls)
i = 0
while i < n:
    l = tls[i]
    l = l[0:-1]
    cmd = "g++ "+l[7:]
    print("\n"+str(i)+":"+ cmd +"\n")
    os.system(cmd)
    s = int(input("0 to exit\t 1 to continue\t 2 to run again: "))
    if s==0: 
        break
    if s==2:
        i-=1
    i+=1

"""26-37,40,43,44,45,56,59,"""