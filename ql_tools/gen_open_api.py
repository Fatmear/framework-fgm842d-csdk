#!/usr/bin/env python

import os,sys,shutil
import re
import hashlib
from sys import path
import copyright

RETURN_SIGNED_INTEGER = 1
RETURN_UNSIGNED_INTEGER = 2
RETURN_POINTOR = 3
RETURN_BOOL = 4
RETURN_VOID = 5
RETURN_BITMAP = 6

pub_h_file_list=[]
api_name_list=[]
api_def_list=[]
api_ptr_list=[]

if len(sys.argv) < 5:
    sys.exit()

currentPath = os.getcwd().replace('/','/') 
api_list_abs_path=sys.argv[1]
export_abs_path=sys.argv[2]
stub_abs_path=sys.argv[3]
usage=sys.argv[4]


open_api_list = 'open_api.list'
open_export_api_c_file = 'ql_open_get_api.c'
open_stub_api_c_file = 'ql_open_api.c'

if os.path.exists(open_export_api_c_file):
    os.remove(open_export_api_c_file)

if os.path.exists(open_stub_api_c_file):
    os.remove(open_stub_api_c_file)


def get_export_api_list():
    api_list=[]
    api_func = False
    with open(api_list_abs_path+'/'+ open_api_list,"r") as f1:
        f1.seek(0)
        comments = False
        for line in f1:
            line = line.strip()
            if api_func == False:
                if line.startswith("@1.0"):
                    api_func = True
            else:
                if line.startswith("//") == True or (line.startswith("/*") == True and line.endswith("*/") == True):
                    continue
                if line.startswith("#if") == True and "0" in line:
                    comments = True
                    continue
                if line.startswith("#endif"):
                    comments = False
                    continue
                if len(line) != 0 and comments == False:
                    api_list.append(line)
    return api_list

def find_api_definition(api_name, h_file_list):
    api_found = False
    api_definition=""
    for file in h_file_list:
        file_path = str(file) 
        with open(file_path,"r") as f1:
            f1.seek(0)
            comments = False
            for line in f1:
                line = line.strip()                
                if (line.startswith("#if") == True and "0" in line) or (line.startswith("/*") == True and line.endswith("*/") == False):
                    comments = True
                    continue

                if comments == True: 
                    if line.startswith("#endif") == True or line.endswith("*/") == True or line.startswith("*/") == True:
                       comments = False
                    continue

                if api_found == False and (re.match("[#\/*({:\",)}\[\]<>;!]", line) != None or re.match("typedef", line) != None \
                   or (line.find("/*") != -1 and line.find("*/") != -1 and api_name in line[line.find("/*"):line.find("*/")])):
                    continue

                if api_name in line:
                    temp1 = line[0:line.find(api_name)+len(api_name)]
                    #print("temp1: "+temp1)
                    temp2 = line[line.find(temp1)+len(temp1):]
                    temp2 = temp2.lstrip()
                    #print("temp2: "+temp2)
                    line = temp1+temp2
                                      
                if api_found == False and api_name+"(" in line:
                    api_found = True

                if api_found == True and len(line) > 0:
                    if len(api_definition) > 0:
                        api_definition += "\n"                       
                    api_definition += line;
                    
                if len(api_definition) > 0 and ";" in api_definition:
                    h_file = os.path.basename(file_path)
                    if "lwip" in file_path:
                        h_file = "lwip/"+h_file
                    elif "mbedtls" in file_path:
                        h_file = "mbedtls/"+h_file
                    if h_file not in pub_h_file_list:
                        pub_h_file_list.append(h_file)
                    break
        f1.close() 
        if api_found == True:
           break
    #print("api "+api_name+" "+api_definition)
    return  api_definition

def list_all_h_file(src_path):
    h_file_list=[]
    for file in os.listdir(src_path):
        file_path = os.path.join(src_path, file)             
        if os.path.isfile(file_path):
            if file_path.endswith(".h") == True:
               h_file_list.append(file_path)
        else:
            temp_list = list_all_h_file(file_path)
            if len(temp_list) > 0:
                h_file_list += temp_list 
    return h_file_list


def get_function_name(str):
    if str.find('(') != -1 :
        str = str[0:str.find('(')] 
    if "const" in str:
       str = str[str.find("const")+len("const"):] 
    if "unsigned" in str:
       str = str[str.find("unsigned")+len("unsigned"):]
    if "*" in str:
       str = str[str.find("*")+1:]
    str = str.lstrip()
    if str.find(' ') != -1:
        str = str[str.find(' ')+1:]      
    return str

def get_function_args(cmd_line):
    arg_list=[]
    cmd_line = cmd_line.lstrip()
    cmd_line = cmd_line.rstrip()

    while len(cmd_line) > 0:
        arg=""
        if cmd_line.find(",") == -1:
            l1 = cmd_line
            cmd_line=cmd_line[len(l1):]
        else:
            l1 = cmd_line[0: cmd_line.find(",")]
            cmd_line=cmd_line[len(l1)+1:]
        l1 = l1.rstrip()
        if "(" not in l1:
            if l1.rfind(" ") != -1:
                arg = l1[l1.rfind(" "):]
            else:#void
                arg = l1.strip() 
        else:
            if l1.endswith(")") == False:#int(*f)(int*,int)                
                l2 = cmd_line[0:cmd_line.find(")")]
                cmd_line=cmd_line[len(l2)+1:]
                if cmd_line.find(",") != -1:
                    l3 = cmd_line[0:cmd_line.find(",")]
                    cmd_line=cmd_line[len(l3)+1:]
                    l2 += l3
                l1 += l2
            arg = l1[l1.find("*"):l1.find(")")]
        #print(arg)
        arg = re.sub('[*]','', arg)
        if "[" in arg and "]" in arg:
            arg = re.sub('[\[1-9\]]+','',arg)       
        if "void" != arg.lower():
            arg_list.append(arg)

    return arg_list             
    
def get_function_return_type(type_str):    
    ret_type_str = type_str.lower().lstrip()
    if "*" in ret_type_str:
        return RETURN_POINTOR
    elif ret_type_str.startswith("bit_mask"):
        return RETURN_BITMAP
    elif ret_type_str.startswith("void"):
        return RETURN_VOID
    elif ret_type_str.startswith("int") or ret_type_str.startswith("char")  or ret_type_str.startswith("short") :
        return RETURN_SIGNED_INTEGER
    elif ret_type_str.startswith("bool"):
        return RETURN_BOOL
    else: 
        return RETURN_UNSIGNED_INTEGER

def gen_api_ptr(api_def):
    api_name = get_function_name(api_def)
    api_ptr = "typedef "
    api_ptr += api_def[0:api_def.find(api_name)]
    api_ptr += "(*_api_"
    api_ptr += api_def[api_def.find(api_name): api_def.find("(")].strip()
    api_ptr += "_cb_t"
    api_ptr +=")"
    api_ptr.strip()
    api_ptr += api_def[api_def.find("("):]
    return api_ptr

def gen_api_body(api_interface):
    api_name = get_function_name(api_interface)
    ret_type_str = api_interface[0:api_interface.find(api_name)].strip()
    ret_type = get_function_return_type(ret_type_str)
    exclude_arg=""
    api_arg_list = get_function_args(api_interface[api_interface.find("(")+1 : api_interface.rfind(")")])
    body = api_interface[0:api_interface.find(";")]
    body +="\n{\n"
    body +="    if (api_tbl."+api_name+" == NULL){\n"
    body +="        int func_addr = 0x00;\n"
    body +="        if((func_addr = m_get_api_ptr((char*)__FUNCTION__)) == 0x00){\n"
    body +="           SDK_API_DEBUG_NOTSUP();\n"
    if ret_type == RETURN_POINTOR:
        body +="           return ("+ret_type_str+")NULL;\n"
    elif ret_type == RETURN_BITMAP:
        body +="           "+ret_type_str+" temp_val;\n"
        body +="           memset(&temp_val, 0x00, sizeof("+ret_type_str+"));\n"
        body +="           return temp_val;\n"
    elif ret_type == RETURN_VOID:
        body +="           return;\n"
    elif ret_type == RETURN_UNSIGNED_INTEGER:
        body +="           return ("+ret_type_str+")0;\n"
    elif ret_type == RETURN_BOOL:
        body +="           return false;\n"
    else:
        body +="           return ("+ret_type_str+")-1;\n"
    body +="        }\n"
    body +="        api_tbl."+api_name+" = (_api_"+api_name.strip()+"_cb_t)func_addr;\n" 
    body +="    }\n"

    if "#if" in api_interface:
        exclude_arg=api_interface[api_interface.find("#if"):api_interface.find("#endif")]
        exclude_arg=exclude_arg[exclude_arg.find("\n")+1:]
        temp_list = api_interface.split("\n")
        for line in temp_list:
            if "#if" in str(line):
                body +="\n"+str(line)
                body +="\n"+"    return api_tbl."+api_name+"("
                for arg in api_arg_list:
                    body += str(arg)+","
                body = body[0:-1]
                body +=");"
            if "#endif" in str(line):
                body +="\n"+"#else"
   
    body +="\n"+"    return api_tbl."+api_name.lstrip()+"("
    if len(api_arg_list) > 0:
        for arg in api_arg_list:       
            if len(exclude_arg) > 0 and str(arg).strip() in exclude_arg:
                continue
            body += str(arg)+","
        body = body[0:-1]
    body +=");\n"
    if "#if" in api_interface:
        body += "#endif\n"
    body +="}\n\n"
    return body

def generate_stub_open_api_c():
    f1 = open(stub_abs_path +"/"+ open_stub_api_c_file, "w")
    f1.write("#include <stdio.h>\n")
    f1.write("#include <stdlib.h>\n")
    f1.write("#include <string.h>\n")
    f1.write("#include <stdbool.h>\n")
    f1.write("\n#include \"typedef.h\"\n")
    for h_file in pub_h_file_list:
        f1.write("#include \""+str(h_file)+"\"\n")
    f1.write("#include \"ql_app_main.h\"\n\n")

    for api_ptr in api_ptr_list:
        f1.write(str(api_ptr)+"\n")
    
    f1.write("\n\n")
    f1.write("\n\nstatic struct{\n")
    for api_name in api_name_list:
        f1.write("     _api_"+str(api_name).strip()+"_cb_t"+"  "+str(api_name)+";"+"\n")
    f1.write("}api_tbl={\n")
    i = 0
    tbl_str=""
    for api_name in api_name_list:
        if i%20 == 0:
            if i == 0:
                tbl_str = "    NULL,"
            else:
                tbl_str += "\n    NULL,"
        else:
            tbl_str += "NULL,"
        i += 1
    tbl_str = tbl_str[0:-1]
    f1.write(tbl_str)
    f1.write("\n};\n\n")

    for api in api_def_list:
        func_body = gen_api_body(api)
        f1.write(func_body)
    f1.close()


def genrate_get_api_hash_func():
    func_msg = "static u32 get_api_hash(char *api)\n"
    func_msg +="{\n"
    func_msg +="    u32 h,v;\n"
    func_msg +="    char* p;\n"
    func_msg +="    for(h = 0,p = (char *)api; *p ;p++)\n"
    func_msg +="    {\n"
    func_msg +="        h = 5527 * h + 7 * (*p);\n"
    func_msg +="        v = h & 0x0000ffff;\n"
    func_msg +="        h ^= v*v;\n"
    func_msg +="    }\n"
    func_msg +="    return h;\n"
    func_msg +="}\n"
    return func_msg

def genrate_MatchInList_func():
    func_msg = "static u32 MatchInList(u32 hash, const ql_open_api_list* hashlist, s32 list_max)\n" 
    func_msg +="{\n"
    func_msg +="    u32 iMax = list_max - 1, iMin = 0;\n"
    func_msg +="    if( hash<hashlist[iMin].hash|| hash>hashlist[iMax].hash)\n"
    func_msg +="    do{\n"
    func_msg +="        if( hash > hashlist[iMin+(iMax-iMin)/2].hash)\n"
    func_msg +="          iMin = iMin+(iMax-iMin)/2;\n"
    func_msg +="        else\n"
    func_msg +="          iMax = iMin+(iMax-iMin)/2;\n"
    func_msg +="    }while( (iMax-iMin)>1 );\n"
    func_msg +="    if( hash == hashlist[iMax].hash)\n"
    func_msg +="    {\n"
    func_msg +="        return iMax;\n"
    func_msg +="    }\n"
    func_msg +="    else if( hash == hashlist[iMin].hash)\n"
    func_msg +="    {\n"
    func_msg +="        return iMin;\n"
    func_msg +="    }\n"
    func_msg +="    else\n"
    func_msg +="    {\n"
    func_msg +="        return -1;\n"
    func_msg +="    }\n"
    func_msg +="}\n"
    return func_msg

def generate_vm_per_get_fun_ptr_func():
    func_msg = "u32 vm_per_get_fun_ptr(char* func_name)\n"
    func_msg +="{\n"
    func_msg +="    u32        resid = -1;\n"
    func_msg +="    u32        hashvalue = 0;\n"
    func_msg +="    if( func_name == NULL )\n"
    func_msg +="    {\n"
    func_msg +="        return 0;\n"
    func_msg +="    }\n"
    func_msg +="    hashvalue = get_api_hash( func_name );\n"
    func_msg +="    resid = MatchInList( hashvalue, vAPITable, MAX_API_NUM);\n"

    func_msg +="    if( (resid >= 0) && (resid < MAX_API_NUM))\n"
    func_msg +="        return (u32)vAPITable[resid].api_ptr;\n"
    func_msg +="    else\n"
    func_msg +="        return 0;\n"
    func_msg +="}\n"

    return func_msg

def generate_export_open_api_c():
    f2 = open(export_abs_path +"/"+ open_export_api_c_file, "w")
    f2.write("#include <stdio.h>\n")
    f2.write("#include <stdlib.h>\n")
    f2.write("#include <string.h>\n")
    f2.write("#include <stdbool.h>\n")
    f2.write("#include \"rtos_pub.h\"\n")
    #f2.write('#include "ql_open_api_def.h"\n\n')
    for h_file in pub_h_file_list:
        f2.write("#include \""+str(h_file)+"\"\n")

    f2.write("typedef struct\n")
    f2.write("{\n")
    f2.write("    uint64 hash;\n")
    f2.write("    void * api_ptr;\n")
    f2.write("} ql_open_api_list;\n\n")

    file_msg = '\nconst ql_open_api_list vAPITable[] = {\n'

    for api in api_name_list:
        hash_value = hash(api) & 0x7FFFFFFFFFFFFFFF
        file_msg = file_msg + '  {  ' + str(hash_value) + ',    ' + '(void *)' + api + '},\n'
    file_msg = file_msg + '};\n'
    f2.write(file_msg)
    f2.write("\n#define MAX_API_NUM        (sizeof(vAPITable)/sizeof(vAPITable[0]))\n\n")
    f2.write("\nu32 vm_per_get_fun_ptr(char* func_name );\n\n")
    func_msg = genrate_get_api_hash_func()
    f2.write(func_msg)
    func_msg = genrate_MatchInList_func()
    f2.write(func_msg)
    func_msg = generate_vm_per_get_fun_ptr_func()
    f2.write(func_msg)    
    

if __name__ == '__main__':
    if "01" in usage:
        file_list = list_all_h_file("./quectel/quec_adapt/")
        file_list += list_all_h_file("./beken378/func/lwip_intf/lwip-2.0.2")
        file_list += list_all_h_file("./beken378/func/mbedtls/mbedtls")
    else:
        file_list = list_all_h_file("./ql_components/api")
        file_list += list_all_h_file("./ql_components/third_party/lwip_intf/lwip-2.0.2")
        file_list += list_all_h_file("./ql_components/third_party/mbedtls/mbedtls")
    pub_api_list = get_export_api_list()
    for api in pub_api_list:
        api_def = find_api_definition(api, file_list)
        if len(api_def) > 0:
           if "extern" in api_def:
               api_def = api_def[api_def.find("extern")+len("extern"):]
           if "MBEDTLS_DEPRECATED" in api_def:
               api_def = api_def[api_def.find("MBEDTLS_DEPRECATED")+len("MBEDTLS_DEPRECATED"):]
           if re.search("#if", api_def) == None:
               api_def = re.sub('[\n]','',api_def)            
           api_def = api_def.lstrip()
           api_def = api_def.rstrip()
           api_def_list.append(api_def)
           api_ptr_list.append(gen_api_ptr(api_def)) 
           api_name_list.append(get_function_name(api_def).strip())

    if len(api_name_list) > 0:
        generate_export_open_api_c()
    if len(api_def_list) > 0 and len(api_ptr_list) > 0:
        generate_stub_open_api_c()

    api_files=[stub_abs_path+"/"+open_stub_api_c_file,
               export_abs_path+"/"+open_export_api_c_file]
    copyright.judge_copyright(api_files)

    
    
