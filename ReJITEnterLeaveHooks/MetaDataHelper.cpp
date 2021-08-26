#include "MetadataHelper.h"
#include <string>


MetadataHelper::MetadataHelper()
{

}

MetadataHelper::~MetadataHelper()
{

}

HRESULT MetadataHelper::GetTypeDefs(IMetaDataImport* metadata, mdTypeDef** typeDefArray, ULONG* typeDefArraySize)
{
    HCORENUM enumTypeDefs = 0;
    ULONG typeDefSize = 0;
    ULONG dummyCount = 0;
    ULONG tokenCount = 0;
    HRESULT hr = S_OK;
    mdTypeDef typeDefToken = 0;
    hr = metadata->EnumTypeDefs(&enumTypeDefs, &typeDefToken, 1, &dummyCount);
    hr = metadata->CountEnum(enumTypeDefs, &typeDefSize);
    *typeDefArray = new mdTypeDef[typeDefSize];
    metadata->CloseEnum(enumTypeDefs);
    enumTypeDefs = 0;
    hr = metadata->EnumTypeDefs(&enumTypeDefs, *typeDefArray, typeDefSize, &tokenCount);
    metadata->CloseEnum(enumTypeDefs);
    *typeDefArraySize = tokenCount;
    return hr;
}

HRESULT MetadataHelper::GetTypeRefs(IMetaDataImport* metadata, mdTypeRef** typeRefArray, ULONG* typeRefArraySize)
{
    HCORENUM enumTypeRefs = 0;
    ULONG typeRefSize = 0;
    ULONG dummyCount = 0;
    ULONG tokenCount = 0;
    HRESULT hr = S_OK;
    mdTypeRef typeRefToken = 0;
    hr = metadata->EnumTypeRefs(&enumTypeRefs, &typeRefToken, 1, &dummyCount);
    hr = metadata->CountEnum(enumTypeRefs, &typeRefSize);
    *typeRefArray = new mdTypeRef[typeRefSize];
    metadata->CloseEnum(enumTypeRefs);
    enumTypeRefs = 0;
    hr = metadata->EnumTypeRefs(&enumTypeRefs, *typeRefArray, typeRefSize, &tokenCount);
    metadata->CloseEnum(enumTypeRefs);
    *typeRefArraySize = tokenCount;
    return hr;
}

HRESULT MetadataHelper::FindTypeDef(IMetaDataImport* pMetaDataImport, const WCHAR* typeName, mdTypeDef* typeDef)
{
    HRESULT hr = S_OK;
    ULONG typeDefSize = 0;
    mdTypeDef* typeDefArray = nullptr;
    hr = GetTypeDefs(pMetaDataImport, &typeDefArray, &typeDefSize);
    if (hr != S_OK)
        return hr;

    *typeDef = mdTypeDefNil;
    for (ULONG i = 0;i < typeDefSize;i++)
    {
        ULONG len = 0;
        mdToken resolutionScope = 0;
        DWORD flags;
        WCHAR szTypeDef[1024];
        mdToken baseType;
        hr = pMetaDataImport->GetTypeDefProps(typeDefArray[i], szTypeDef, 1024, &len, &flags, &baseType);
        if (hr == S_OK)
        {
            if (wcscmp(typeName, szTypeDef) == 0)
            {
                *typeDef = typeDefArray[i];
                break;
            }
        }
    }
    delete[] typeDefArray;
    hr = (*typeDef != mdTypeDefNil ? S_OK : E_FAIL);
    return hr;
}

HRESULT MetadataHelper::GetMemberRefs(IMetaDataImport* metadata, mdTypeRef typeRefToken, mdMemberRef** memberRefArray, ULONG* memberRefArraySize)
{
    HCORENUM enumMemberRefs = 0;
    mdMemberRef memberRef = 0;
    ULONG dummyCount = 0;
    ULONG tokenCount = 0;
    ULONG memberRefSize = 0;
    HRESULT hr = S_OK;
    hr = metadata->EnumMemberRefs(&enumMemberRefs, typeRefToken, &memberRef, 1, &dummyCount);
    hr = metadata->CountEnum(enumMemberRefs, &memberRefSize);
    *memberRefArray = new mdMemberRef[memberRefSize];
    metadata->CloseEnum(enumMemberRefs);
    enumMemberRefs = 0;
    hr = metadata->EnumMemberRefs(&enumMemberRefs, typeRefToken, *memberRefArray, memberRefSize, &tokenCount);
    metadata->CloseEnum(enumMemberRefs);
    *memberRefArraySize = tokenCount;
    return tokenCount;
}

HRESULT MetadataHelper::GetMemberDefs(IMetaDataImport* metadata, mdTypeDef typeDefToken, mdToken** memberDefArray, ULONG* memberDefArraySize)
{
    HCORENUM enumMemberDefs = 0;
    mdToken memberDef = 0;
    ULONG dummyCount = 0;
    ULONG tokenCount = 0;
    ULONG memberDefSize = 0;
    HRESULT hr = S_OK;
    hr = metadata->EnumMethods(&enumMemberDefs, typeDefToken, &memberDef, 1, &dummyCount);
    hr = metadata->CountEnum(enumMemberDefs, &memberDefSize);
    *memberDefArray = new mdToken[memberDefSize];
    metadata->CloseEnum(enumMemberDefs);
    enumMemberDefs = 0;
    hr = metadata->EnumMethods(&enumMemberDefs, typeDefToken, *memberDefArray, memberDefSize, &tokenCount);
    metadata->CloseEnum(enumMemberDefs);
    *memberDefArraySize = tokenCount;
    return tokenCount;
}

HRESULT MetadataHelper::FindMemberRef(IMetaDataImport* metadata, const WCHAR* methodName, mdTypeRef typeRef, mdMemberRef* memberRef)
{
    HRESULT hr = S_OK;
    ULONG memberRefSize = 0;
    mdMemberRef* memberRefArray = nullptr;
    hr = GetMemberRefs(metadata, typeRef, &memberRefArray, &memberRefSize);
    *memberRef = mdTypeRefNil;
    for (ULONG i = 0;i < memberRefSize;i++)
    {
        mdToken token = 0;
        WCHAR currentMemberName[1024];
        PCCOR_SIGNATURE sig;
        ULONG len2 = 0;
        ULONG sigSize = 0;

        hr = metadata->GetMemberRefProps(memberRefArray[i], &token, currentMemberName, sizeof(currentMemberName), &len2, &sig, &sigSize);
        if (hr == S_OK)
        {
            if (wcscmp(methodName, currentMemberName) == 0)
            {
                *memberRef = memberRefArray[i];
                break;
            }
        }
    }
    delete[] memberRefArray;
    hr = (*memberRef != mdTypeRefNil ? S_OK : E_FAIL);
    return hr;
}

HRESULT MetadataHelper::FindMemberDef(IMetaDataImport* metadata, const WCHAR* methodName, mdTypeDef typeDef, mdMemberRef* memberRef)
{
    HRESULT hr = S_OK;
    ULONG memberRefSize = 0;
    mdToken* memberRefArray = nullptr;
    hr = GetMemberDefs(metadata, typeDef, &memberRefArray, &memberRefSize);
    *memberRef = mdTypeRefNil;
    for (ULONG i = 0;i < memberRefSize;i++)
    {
        mdToken token = 0;
        WCHAR currentMemberName[1024];
        PCCOR_SIGNATURE sig;
        ULONG len2 = 0;
        ULONG sigSize = 0;

        hr = metadata->GetMethodProps(memberRefArray[i], &token, currentMemberName, sizeof(currentMemberName), &len2, NULL, &sig, &sigSize, NULL, NULL);
        if (hr == S_OK)
        {
            if (wcscmp(methodName, currentMemberName) == 0)
            {
                *memberRef = memberRefArray[i];
                break;
            }
        }
    }
    delete[] memberRefArray;
    hr = (*memberRef != mdTypeRefNil ? S_OK : E_FAIL);
    return hr;
}

HRESULT MetadataHelper::FindTypeRef(IMetaDataImport* pMetaDataImport, const WCHAR* typeName, mdTypeRef* typeRef)
{
    HRESULT hr = S_OK;
    ULONG typeRefSize = 0;
    mdTypeRef* typeRefArray = nullptr;
    hr = GetTypeRefs(pMetaDataImport, &typeRefArray, &typeRefSize);
    if (hr != S_OK)
        return hr;

    *typeRef = mdTypeRefNil;
    for (ULONG i = 0;i < typeRefSize;i++)
    {
        WCHAR currentTypeName[1024];
        ULONG len = 0;
        mdToken resolutionScope = 0;
        hr = pMetaDataImport->GetTypeRefProps(typeRefArray[i], &resolutionScope, currentTypeName, sizeof(currentTypeName) / sizeof(WCHAR), &len);
        if (hr == S_OK)
        {
            if (wcscmp(typeName, currentTypeName) == 0)
            {
                *typeRef = typeRefArray[i];
                break;
            }
        }
    }
    delete[] typeRefArray;
    hr = (*typeRef != mdTypeRefNil ? S_OK : E_FAIL);
    return hr;
}

HRESULT MetadataHelper::ResolveMethodDef(ICorProfilerInfo* info, ModuleID moduleID, const WCHAR* typeName, const WCHAR* methodName, mdTypeDef* outTypeDef, mdMemberRef* outMemberRef)
{
    HRESULT hr = S_OK;
    IMetaDataImport* pMetaDataImport = NULL;

    *outTypeDef = mdTypeDefNil;
    *outMemberRef = mdMemberRefNil;

    hr = info->GetModuleMetaData(moduleID, ofRead, IID_IMetaDataImport, (IUnknown**)&pMetaDataImport);
    if (FAILED(hr))
    {
        return hr;
    }

    mdTypeDef typeDef = mdTypeDefNil;
    mdMemberRef methodRef = mdMemberRefNil;
    hr = FindTypeDef(pMetaDataImport, typeName, &typeDef);
    if (hr != S_OK)
        goto cleanup;
    hr = FindMemberDef(pMetaDataImport, methodName, typeDef, &methodRef);
    if (hr != S_OK)
        goto cleanup;

    *outTypeDef = typeDef;
    *outMemberRef = methodRef;

cleanup:
    pMetaDataImport->Release();
    return hr;
}

HRESULT MetadataHelper::ResolveMethodRef(ICorProfilerInfo* info, ModuleID moduleID, const WCHAR* typeName, const WCHAR* methodName, mdTypeRef* outTypeRef, mdMemberRef* outMemberRef)
{
    HRESULT hr = S_OK;
    IMetaDataImport* pMetaDataImport = NULL;

    *outTypeRef = mdTypeRefNil;
    *outMemberRef = mdMemberRefNil;

    hr = info->GetModuleMetaData(moduleID, ofRead, IID_IMetaDataImport, (IUnknown**)&pMetaDataImport);
    if (FAILED(hr))
    {
        return hr;
    }

    mdTypeRef typeRef = mdTypeRefNil;
    mdMemberRef methodRef = mdMemberRefNil;
    hr = FindTypeRef(pMetaDataImport, typeName, &typeRef);
    if (hr != S_OK)
        goto cleanup;
    hr = FindMemberRef(pMetaDataImport, methodName, typeRef, &methodRef);
    if (hr != S_OK)
        goto cleanup;

    *outTypeRef = typeRef;
    *outMemberRef = methodRef;

cleanup:
    pMetaDataImport->Release();
    return hr;
}
