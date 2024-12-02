/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef LFS_PORT_H
#define LFS_PORT_H

#include "ql_type.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define  QL_FS_NAME_MAX 255


#define QL_SEEK_SET	0	/* Seek from beginning of file.  */
#define QL_SEEK_CUR	1	/* Seek from current position.  */
#define QL_SEEK_END	2	/* Seek from end of file.  */

#define QL_FS_TYPE_FILE           0x001
#define QL_FS_TYPE_DIR            0x002

#define QL_FILE_PRXFIX_UFS 		  "UFS:"
#define QL_FILE_PRXFIX_UFS_LEN	  (4)

#ifndef QFILE
typedef INT32  QFILE;          /* file handler, returned by ql_fopen  */
typedef UINT32 fs_off_t;
typedef UINT32 fs_size_t;
typedef UINT32 fs_block_t;
#endif

/*========================================================================
 *	Enumeration Definition
*========================================================================*/
/** @brief 文件及目录操作相关错误码*/
typedef enum
{
	QL_FS_OK = 0,
	QL_FS_INVALID_INPUT_VALUE	 	= -1,     				//输入值无效
	QL_FS_LARGER_THAN_FILESIZE	 	= -2,					//大于文件大小
	QL_FS_READ_ZERO                 = -3,					//读取0字节
	QL_FS_DRIVE_FULL                = -4,					//驱动已满
	QL_FS_MOV_ERROR                 = -5,					//移除文件错误
	QL_FS_FILE_NOT_FOUND       	    = -6,					//未找到文件
	QL_FS_INVALID_FILE_NAME         = -7,					//无效文件名
	QL_FS_FILE_ALREADY_EXISTED		= -8,					//文件已存在
	QL_FS_FAILED_TO_CREATE_FILE    	= -9,					//创建文件失败
	QL_FS_FAILED_TO_WRITE_FILE     	= -10,					//数据写入文件失败
	QL_FS_FAILED_TO_OPEN_FILE   	= -11,					//打开文件失败
	QL_FS_FAILED_TO_READ_FILE      	= -12,					//读取文件失败
	QL_FS_EXCEED_MAX_LENGTH        	= -13,					//超过最大长度
	QL_FS_REACH_MAX_OPENFILE_NUM   	= -14,					//达到最大打开文件数
	QL_FS_IS_READONLY              	= -15,					//文件只读
	QL_FS_GET_SIZE_FAIL        	 	= -16,					//获取文件大小失败
	QL_FS_INVALID_FILE_DESCRIPTOR  	= -17,					//描述无效
	QL_FS_LIST_FILE_FAIL           	= -18,					//列出文件列表失败
	QL_FS_DELETE_FILE_FAIL         	= -19,					//删除文件失败
	QL_FS_GET_DISK_INFO_FAIL       	= -20,					//获取磁盘信息失败
	QL_FS_NO_SPACE             	 	= -21,					//磁盘空间不足
	QL_FS_TIME_OUT                 	= -22,					//超时
	QL_FS_FILE_NOT_FOUND_2         	= -23,					//未找到文件
	QL_FS_FILE_TOO_LARGE           	= -24,					//文件过大
	QL_FS_FILE_ALREADY_EXIST       	= -25,					//文件已存在
	QL_FS_INVALID_PARAMETER    	 	= -26,					//无效参数
	QL_FS_ALREADY_OPERATION        	= -27,					//文件已打开
	QL_FS_ERROR_GENERAL			 	= -28, 					//通用错误码
	QL_FS_RENAME_ERROR 			 	= -29, 					//重命名文件失败
	QL_FS_QUIT_DATE_MODE 			= -30,
	QL_FS_CLOSE_FAIL			    = -31, 					//关闭文件失败
	QL_FS_SEEK_FAIL				 	= -32, 					//移动文件指针失败
	QL_FS_TELL_FAIL				 	= -33, 					//获取文件指针位置失败
	QL_FS_FAILED_TO_GET_STAT		= -34,					//获取文件信息失败
	QL_FS_NOT_EXIST				 	= -35,					//文件不存在
	QL_FS_RENAME_FAIL				= -36, 					//重命名文件失败
	QL_FS_TRUNCATE_FAIL            	= -37, 					//裁剪文件失败

	//Dir error code
	QL_FS_DIR_MAKE_FAIL 			= -38,					//创建目录失败
	QL_FS_DIR_OPEN_FAIL   			= -39,					//打开目录失败
	QL_FS_DIR_CLOSE_FAIL			= -40,					//关闭目录失败	
	QL_FS_DIR_READ_FAIL				= -41,					//读取目录失败
	QL_FS_DIR_TELL_FAIL				= -42,
	QL_FS_DIR_SEEK_FAIL				= -43,
	QL_FS_DIR_REMOVE_FAIL			= -44,					//移除目录失败
	QL_FS_DIR_DIR_ALREADY_EXIST		= -45,					//目录已存在

	QL_FS_ERROR_MAX,
}ql_file_errcode_e;
/*===========================================================================
 *	Struct Definition
 ===========================================================================*/
/** @brief 文件信息结构体*/
struct stat {
    unsigned char        type;						//文件类型, reserved
    unsigned int         size;						//文件大小
    char                 name[QL_FS_NAME_MAX+1];		//文件名
};


/** @brief 目录信息句柄*/
typedef struct
{
    int         			fs_index;		//目录索引
    int         			_reserved;		//保留参数
}QDIR;

/** @brief 目录信息结构体*/
typedef struct
{
    int                    d_ino;           //Inode号
    unsigned char          d_type;		  	//目录类型
    char                   d_name[256];     //目录名
}qdirent;

int ql_fs_init();

int ql_fs_deinit();

/*========================================================================
 *	function Definition
 *========================================================================*/
/**
 * @brief					打开/创建一个文件
 * @param	file_name		文件名
 * @param	mode			打开模式
 * @return	QFILE:文件句柄
 */
QFILE ql_fopen(const char *file_name, const char *mode);

/**
 * @brief					关闭一个文件
 * @param	fd				文件句柄
 * @return	ql_file_errcode_e
 */
int ql_fclose(QFILE fd);


/**
 * @brief					移除一个文件
 * @param	file_name		文件名
 * @return	ql_file_errcode_e
 */
int ql_remove(const char *file_name);

/*****************************************************************
* Function: ql_fread
*
* Description:从指定文件中读取数据
*	
* Parameters:
*	buffer			[out]		存储读取数据的内存地址。不可为空指针
*	size			[in]		需读取的每个元素大小。单位：字节。
*	num				[in]		需读取的元素个数。最终读取数据大小为size*num
*	fd				[in]		文件句柄
*
* Return:
*	> 0 					成功读取的字节数。
*	other					错误码。
*
*****************************************************************/
/**
 * @brief					从指定文件中读取数据
 * @param	buffer			存储读取数据的内存地址。不可为空指针
 * @param	size			需读取的每个元素大小。单位：字节。
 * @param	num				需读取的元素个数。最终读取数据大小为size*num
 * @param	fd				文件句柄
 * @return	ql_file_errcode_e
 */
int ql_fread(void * buffer, size_t size, size_t num, QFILE fd);


/**
 * @brief					向指定文件中写入数据
 * @param	buffer			存储写入数据的内存地址。不可为空指针
 * @param	size			需写入的每个元素大小。单位：字节
 * @param	num				需写入的元素个数。最终写入数据大小为size*num
 * @param	fd				文件句柄
 * @return	ql_file_errcode_e
 */
int ql_fwrite(void * buffer, size_t size, size_t num, QFILE fd);

/**
 * @brief					设置文件指针的位置
 * @param	fd				文件句柄
 * @param	offset			偏移量
 * @param	origin			偏移起始位置
 * @return	ql_file_errcode_e
 */
int ql_fseek(QFILE fd, long offset, int origin);


/**
 * @brief					设置文件指针于文件开头
 * @param	fd				文件句柄
 * @return	ql_file_errcode_e
 */
int ql_frewind(QFILE fd);


/**
 * @brief					获取文件指针相对于文件开头的偏移值
 * @param	fd				文件句柄
 * @return	ql_file_errcode_e
 */
int ql_ftell(QFILE fd);


/**
 * @brief					通过文件句柄获取文件状态
 * @param	fd				文件句柄
 * @param	st				文件状态结构体
 * @return	ql_file_errcode_e
 */
int ql_fstat(QFILE fd, struct stat *st);


/**
 * @brief					通过文件名获取文件状态
 * @param	file_name		文件名
 * @param	st				文件状态结构体
 * @return	ql_file_errcode_e
 */
int ql_stat(const char *file_name, struct stat *st);


/**
 * @brief					从文件开头截取文件为指定长度
 * @param	fd				文件句柄
 * @param	length			指定长度
 * @return	ql_file_errcode_e
 */
int ql_ftruncate(QFILE fd, uint length);


/**
 * @brief					获取文件大小
 * @param	fd				文件句柄
 * @return	文件大小
 */
int ql_fsize(QFILE fd);


/**
 * @brief					判断文件是否存在
 * @param	file_path		文件名
 * @return	0:存在;	other:错误码
 */
int ql_file_exist(const char *file_path);


/**
 * @brief					创建一个目录
 * @param	path			目录名(带路径)
 * @param	mode			模式
 * @return	ql_file_errcode_e
 */
int ql_mkdir(const char *path, uint mode);

/**
 * @brief					打开指定目录
 * @param	path			目录名(带路径)
 * @return	other:目录句柄;	NULL:失败
 */
QDIR *ql_opendir(const char *path);


/**
 * @brief					关闭指定目录
 * @param	pdir			目录句柄
 * @return	ql_file_errcode_e
 */
int ql_closedir(QDIR *pdir);


/**
 * @brief					从指定目录中获取文件信息
 * @param	pdir			目录句柄
 * @return	other:目录信息结构体;	NULL:失败
 */
qdirent *ql_readdir(QDIR *pdir);


/**
 * @brief					删除指定目录
 * @param	path			目录名(带路径)
 * @return	ql_file_errcode_e
 */
int ql_rmdir(const CHAR *path);


/**
 * @brief					重命名文件。
 * @param	oldpath			原文件名
 * @param	newpath			新文件名
 * @return	ql_file_errcode_e
 */
int ql_rename(const char *oldpath, const char *newpath);
/**
 * @brief						同步内存中已修改的文件数据到储存设备
 * @param	fd					文件句柄
 * @return	ql_file_errcode_e
 */
int ql_fsync(QFILE fd);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
