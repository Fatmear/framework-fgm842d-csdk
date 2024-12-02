# !/usr/bin/python
# -*- coding: UTF-8 -*-
import os
import re
import datetime


#获取所有符合的文件路径|.h|.cpp.|.py
def get_file(path):
    files = []
    file_suffixes=['.c','.h','.cpp','.mak' '.inc','.py']
    for dirpath, dirnames, filenames in os.walk(path):
        if filenames !=[]:
            for filename in filenames:
                file_suffix = os.path.splitext(filename)[1]    #文件后缀
                if file_suffix in file_suffixes:
                    files = files + [dirpath + '/' + filename]
    return files


#查看文件是否已加版权,有则不加，无则加
def judge_copyright(files):
    for file in files:
        pattern = '.*/(.*)'
        file_name = re.findall(pattern, file)
        print(file_name)
        quectel_file= re.findall("^(quec|ql).*",file_name[0])
        if quectel_file!=[]:
            #动态添加文件名和年份
            copyright_info = '''
/**  @file
  {}

  @brief
  TODO

*/

/*================================================================
  Copyright (c) {} Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/
                '''.format(file_name[0], datetime.datetime.now().year)
            copyright_info_py = '''
#   @file
#   {}
#
#   @brief
#   TODO
#
#
#
# ================================================================
#   Copyright (c) {} Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
#   Quectel Wireless Solution Proprietary and Confidential.
# =================================================================
# =================================================================
#
#                         EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# WHEN              WHO         WHAT, WHERE, WHY
# ------------     -------     -------------------------------------------------------------------------------
#
# =================================================================    '''.format(file_name[0], datetime.datetime.now().year)
            # str to bytes
            copyright_info_py = bytes(copyright_info_py, encoding="utf-8")
            copyright_info = bytes(copyright_info, encoding="utf-8")

            with open(file, 'rb+') as f:
                content = f.read()
                #去除bom编码的文件格式
                if content.startswith(b'\xef\xbb\xbf'):
                    content = content[3:]

                #查看是否已有版权信息
                if re.search(b'.*Copyright.*',content,re.I):
                    print(file+"    :this file have copyright already!!")
                else:
                    try:
                        f.seek(0,0)
                        if file.endswith('.py') or file.endswith('.mak') or file.endswith('.inc'):
                            text = copyright_info_py + b'\n' + content
                        else:
                            text = copyright_info + b'\n'  + content
                        f.write(text)
                        print(file+"：   add successful")
                    except Exception as e:
                        pass
                        print(file +"：add copyright error: ", e)




if __name__ == '__main__':
    path = os.path.abspath(os.path.join(os.getcwd(), ".\middleware\quectel"))
    files = get_file(path)      #可将path写死

    judge_copyright(files)



