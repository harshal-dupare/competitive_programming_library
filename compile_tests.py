import os
import subprocess

test_my_lib = "test_my_lib.txt"
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


for l in tls:
    l = l[0:-1]
    cmd = "g++ "+l[7:]
    print("\n"+cmd+"\n")
    os.system(cmd)