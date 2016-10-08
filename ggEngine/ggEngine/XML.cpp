#include "XML.h"
#pragma warning(disable : 4127)  // conditional expression is constant
#define CHKHR(stmt)             do { hr = (stmt); if (FAILED(hr)) {SafeRelease(pFileStream);SafeRelease(pReader); } while(0)
#define HR(stmt)                do { hr = (stmt); {SafeRelease(pFileStream);SafeRelease(pReader); } } while(0)
#include "Helper.h"
namespace ggEngine {
	XML::XML(std::string path)
	{
		LPCSTR file = path.c_str();

		IStream *pFileStream = NULL;
		IXmlReader *pReader = NULL;
		HRESULT hr;
		//Open read-only input stream
		if (FAILED(hr = SHCreateStreamOnFile(file, STGM_READ, &pFileStream)))
		{
			wprintf(L"Error creating file reader, error is %08.8lx", hr);
			fileNotFound = true;
			HR(hr);
		}

		if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL)))
		{
			wprintf(L"Error creating xml reader, error is %08.8lx", hr);
			HR(hr);
		}

		if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
		{
			wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
			HR(hr);
		}

		if (FAILED(hr = pReader->SetInput(pFileStream)))
		{
			wprintf(L"Error setting input for reader, error is %08.8lx", hr);
			HR(hr);
		}
		ConstructAtlasSpriteInfo(pReader, pFileStream);
		//read until there are no more nodes

		SafeRelease(pFileStream);
		SafeRelease(pReader);
		return;
	}

	XML::~XML()
	{
	}
	std::vector<AtlasSpriteInfo> XML::GetSpriteList()
	{
		if (!fileNotFound) {
			return spriteList;
		}
	}
	void XML::SafeRelease(IStream * pStream)
	{
		do { if (pStream) { pStream->Release(); } pStream = NULL; } while (0);
	}
	void XML::SafeRelease(IXmlReader * pReader)
	{
		do { if (pReader) { pReader->Release(); } pReader = NULL; } while (0);
	}
	std::vector<AtlasSpriteInfo>  XML::ConstructAtlasSpriteInfo(IXmlReader * pReader, IStream *pFileStream)
	{
		UINT cwchPrefix;
		HRESULT hr = S_OK;
		const WCHAR* pwszPrefix;
		const WCHAR* pwszLocalName;
		const WCHAR* pwszValue;
		XmlNodeType nodeType;
		AtlasSpriteInfo atlasSpriteInfo;
		while (S_OK == (hr = pReader->Read(&nodeType)))
		{
			switch (nodeType)
			{
			case XmlNodeType_XmlDeclaration:
				wprintf(L"XmlDeclaration\n");
				if (FAILED(hr = WriteAttributes(pReader,NULL)))
				{
					wprintf(L"Error writing attributes, error is %08.8lx", hr);
					HR(hr);
				}
				break;
			case XmlNodeType_Element:
				if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
				{
					wprintf(L"Error getting prefix, error is %08.8lx", hr);
					HR(hr);
				}
				if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
				{
					wprintf(L"Error getting local name, error is %08.8lx", hr);
					HR(hr);
				}
				if (cwchPrefix > 0)
					wprintf(L"Element: %s:%s\n", pwszPrefix, pwszLocalName);
				else
					wprintf(L"Element: %s\n", pwszLocalName);
				if (FAILED(hr = WriteAttributes(pReader,&atlasSpriteInfo)))
				{
					wprintf(L"Error writing attributes, error is %08.8lx", hr);
					HR(hr);
				}
				if (Helper::WCharToString(pwszLocalName) != "TextureAtlas") {
					spriteList.push_back(atlasSpriteInfo);
				}

				if (pReader->IsEmptyElement())
					wprintf(L" (empty)");
				break;
			case XmlNodeType_EndElement:
				if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
				{
					wprintf(L"Error getting prefix, error is %08.8lx", hr);
					HR(hr);
				}
				if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
				{
					wprintf(L"Error getting local name, error is %08.8lx", hr);
					HR(hr);
				}
				if (cwchPrefix > 0)
					wprintf(L"End Element: %s:%s\n", pwszPrefix, pwszLocalName);
				else
					wprintf(L"End Element: %s\n", pwszLocalName);
				break;
			case XmlNodeType_Text:
			case XmlNodeType_Whitespace:
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					HR(hr);
				}
				wprintf(L"Text: >%s<\n", pwszValue);
				break;
			case XmlNodeType_CDATA:
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					HR(hr);
				}
				wprintf(L"CDATA: %s\n", pwszValue);
				break;
			case XmlNodeType_ProcessingInstruction:
				if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
				{
					wprintf(L"Error getting name, error is %08.8lx", hr);
					HR(hr);
				}
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					HR(hr);
				}
				wprintf(L"Processing Instruction name:%s value:%s\n", pwszLocalName, pwszValue);
				break;
			case XmlNodeType_Comment:
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					HR(hr);
				}
				wprintf(L"Comment: %s\n", pwszValue);
				break;
			case XmlNodeType_DocumentType:
				wprintf(L"DOCTYPE is not printed\n");
				break;
			}
		}
		return spriteList;
	}
	HRESULT XML::WriteAttributes(IXmlReader* pReader, AtlasSpriteInfo *atlasSpriteInfo)
	{
		const WCHAR* pwszPrefix;
		const WCHAR* pwszLocalName;
		const WCHAR* pwszValue;
		HRESULT hr = pReader->MoveToFirstAttribute();

		if (S_FALSE == hr)
			return hr;
		if (S_OK != hr)
		{
			wprintf(L"Error moving to first attribute, error is %08.8lx", hr);
			return hr;
		}
		else
		{
			while (TRUE)
			{
				if (!pReader->IsDefault())
				{
					UINT cwchPrefix;
					if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
					{
						wprintf(L"Error getting prefix, error is %08.8lx", hr);
						return hr;
					}
					if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
					{
						wprintf(L"Error getting local name, error is %08.8lx", hr);
						return hr;
					}
					if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
					{
						wprintf(L"Error getting value, error is %08.8lx", hr);
						return hr;
					}
					if (cwchPrefix > 0)
						wprintf(L"Attr: %s:%s=\"%s\" \n", pwszPrefix, pwszLocalName, pwszValue);
					else
						wprintf(L"Attr: %s=\"%s\" \n", pwszLocalName, pwszValue);
					std::string key = Helper::WCharToString(pwszLocalName);
					std::string value = Helper::WCharToString(pwszValue);
					if (atlasSpriteInfo != NULL) {
						if (key == "name") {
							atlasSpriteInfo->name = value;
						}
						else if (key == "x") {
							atlasSpriteInfo->x = std::stof(value);
						}
						else if (key == "y") {
							atlasSpriteInfo->y = std::stof(value);
						}
						else if (key == "width") {
							atlasSpriteInfo->width = std::stof(value);
						}
						else if (key == "height") {
							atlasSpriteInfo->height = std::stof(value);
						}
					}
				}
				if (S_OK != pReader->MoveToNextAttribute())
					break;
			}
		}
		return hr;
	}
}
