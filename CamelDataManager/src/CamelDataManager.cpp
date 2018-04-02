﻿/*!
 *@file CamelDataManager.h
 *@brief CamelDataManager
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "CamelDataManager.h"
#include <QFileInfo>

CamelDataManager::CamelDataManager()
{
    Sub_FMInterface = new Camel_FileManagerCInterface();
    Sub_FMInt = Sub_FMInterface->Cls_funInitialize();
    Sub_FMInt->Cls_funManagerInitialize();
    clsFileManager_CmdMapInit();
    m_tableData = new DataTableViewModel();
    //    for (int i = 0; i < 100; i++)
    //    {
    //        m_tableData->add(QStringLiteral("数据")+QString::number(i), QStringLiteral("文件"), QStringLiteral("1.234M"));
    //    }
    m_listData = new DataListViewModel();
    //    for (int i = 0; i < 100; i++)
    //    {
    //        m_listData->add(QStringLiteral("名称")+QString::number(i), QStringLiteral("路径"));
    //    }
}

CamelDataManager::~CamelDataManager()
{
    delete m_tableData;
    delete m_listData;
    Sub_FMInterface->Cls_funTerminate(Sub_FMInt);
    delete Sub_FMInterface;
}

DataTableViewModel *CamelDataManager::getTableData()
{
    return (m_tableData);
}

DataListViewModel *CamelDataManager::getListData()
{
    return (m_listData);
}

int CamelDataManager::cls_funManagerDB_CreateDataBase(QString strName, QString strPass, QString strPath)
{
    string sDBName = strName.toLocal8Bit();
    string sDBPass = strPass.toStdString();
    string sAppPath = strPath.toLocal8Bit();
    string sDBFileName = sAppPath + sDBName + DBSuffix.toStdString();

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_CreateDataBase(&dBVerify, sDBName.c_str(), true);
    if (intError == clsFileManager_intErrorCode_Success)
    {
        m_listData->add(strName, strPath);
        m_strCurDBName = sDBName;
        m_strCurDBPass = sDBPass;
        m_strCurDBPath = sDBFileName;
    }
    return(intError);
}

int CamelDataManager::cls_funManagerDB_OpenDataBase(QString strName, QString strPass, QString strPath)
{
    string sDBName = strName.toLocal8Bit();
    string sDBPass = strPass.toStdString();
    string sAppPath = strPath.toLocal8Bit();
    string sDBFileName = sAppPath + sDBName + DBSuffix.toStdString();

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_OpenDataBase(&dBVerify);
    if (intError == clsFileManager_intErrorCode_Success)
    {
        if (strName.length() == 0)
        {
            QFileInfo fileInfo;
            fileInfo.setFile(strPath);
            strName = fileInfo.fileName();
            strName = strName.replace(DBSuffix, "");
        }
        m_listData->add(strName, strPath);
        m_strCurDBName = sDBName;
        m_strCurDBPass = sDBPass;
        m_strCurDBPath = sDBFileName;
        emit sOpenDataBase(strName, strPath);
    }
    return(intError);
}

int CamelDataManager::cls_funManagerDB_SetName(QString strDBName)
{
    string sDBName = strDBName.toLocal8Bit();
    Cls_stuDBVerify dBVerify(m_strCurDBPath.c_str(), m_strCurDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_SetName(&dBVerify, sDBName.c_str());
    if (intError == clsFileManager_intErrorCode_Success)
    {

    }
    return(intError);
}

int CamelDataManager::cls_funManagerDB_ChangePassword(QString strNewPass)
{
    string sDBPass = strNewPass.toStdString();
    Cls_stuDBVerify dBVerify(m_strCurDBPath.c_str(), m_strCurDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_ChangePassword(&dBVerify, m_strCurDBPass.c_str(), sDBPass.c_str());
    if (intError == clsFileManager_intErrorCode_Success)
    {

    }
    return(intError);
}
