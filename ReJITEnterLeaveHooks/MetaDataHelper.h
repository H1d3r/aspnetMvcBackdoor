#pragma once

#include <cor.h>
#include <corprof.h>

class MetadataHelper
{
public:
    static HRESULT ResolveMethodDef(ICorProfilerInfo* info, ModuleID moduleID, const WCHAR* typeName, const WCHAR* methodName, mdTypeDef* outTypeDef, mdMemberRef* outMemberRef);
    static HRESULT ResolveMethodRef(ICorProfilerInfo* info, ModuleID moduleID, const WCHAR* typeName, const WCHAR* methodName, mdTypeRef* outTypeRef, mdMemberRef* outMemberRef);

private:
    MetadataHelper();
    ~MetadataHelper();
public:
    static HRESULT FindTypeDef(IMetaDataImport* pMetaDataImport, const WCHAR* typeName, mdTypeDef* typeDef);
    static HRESULT FindTypeRef(IMetaDataImport* pMetaDataImport, const WCHAR* typeName, mdTypeRef* typeRef);
    static HRESULT GetTypeDefs(IMetaDataImport* metadata, mdTypeDef** typeDefArray, ULONG* typeDefArraySize);
    static HRESULT GetTypeRefs(IMetaDataImport* metadata, mdTypeRef** typeRefArray, ULONG* typeRefArraySize);
    static HRESULT FindMemberRef(IMetaDataImport* metadata, const WCHAR* methodName, mdTypeRef typeRef, mdMemberRef* memberRef);
    static HRESULT FindMemberDef(IMetaDataImport* metadata, const WCHAR* methodName, mdTypeDef typeDef, mdMemberRef* memberDef);
    static HRESULT GetMemberRefs(IMetaDataImport* metadata, mdTypeRef typeRefToken, mdMemberRef** memberRefArray, ULONG* memberRefArraySize);
    static HRESULT GetMemberDefs(IMetaDataImport* metadata, mdTypeDef typeDefToken, mdToken** memberDefArray, ULONG* memberDefArraySize);
};
