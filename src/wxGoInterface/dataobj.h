WXGO_DECL_TYPECONV(DataFormat)
WXGO_DECL_TYPECONV(DataObject)
WXGO_DECL_TYPECONV(DataObjectComposite)
WXGO_DECL_TYPECONV(DataObjectSimple)
WXGO_DECL_TYPECONV(CustomDataObject)
WXGO_DECL_TYPECONV(BitmapDataObject)
WXGO_DECL_TYPECONV(TextDataObject)
WXGO_DECL_TYPECONV(URLDataObject)
WXGO_DECL_TYPECONV(FileDataObject)
WXGO_DECL_TYPECONV(HTMLDataObject)
class wxDataFormat
{
public:
    wxDataFormat(wxDataFormatId format = wxDF_INVALID);
    wxDataFormat(const wxString& format);
    wxString GetId() const;
    wxDataFormatId GetType() const;
    void SetId(const wxString& format);
    void SetType(wxDataFormatId type);
    bool operator !=(const wxDataFormat& format) const;
    bool operator !=(wxDataFormatId format) const;
    bool operator ==(const wxDataFormat& format) const;
    bool operator ==(wxDataFormatId format) const;
};
const wxDataFormat wxFormatInvalid;
class wxDataObject
{
public:
    enum Direction
    {
        Get  = 0x01,
        Set  = 0x02,
        Both = 0x03
    };
    wxDataObject();
    virtual ~wxDataObject();
    virtual void GetAllFormats(wxDataFormat* formats,
                               Direction dir = Get) const = 0;
    virtual bool GetDataHere(const wxDataFormat& format, void* buf) const = 0;
    virtual size_t GetDataSize(const wxDataFormat& format) const = 0;
    virtual size_t GetFormatCount(Direction dir = Get) const = 0;
    virtual wxDataFormat GetPreferredFormat(Direction dir = Get) const = 0;
    virtual bool SetData(const wxDataFormat& format, size_t len, const void* buf);
    bool IsSupported(const wxDataFormat& format, Direction dir = Get) const;
};
class wxDataObjectComposite : public wxDataObject
{
public:
    wxDataObjectComposite();
    void Add(wxDataObjectSimple* dataObject, bool preferred = false);
    wxDataFormat GetReceivedFormat() const;
    wxDataObjectSimple *GetObject(const wxDataFormat& format,
                                  wxDataObject::Direction dir = wxDataObject::Get) const;
};
class wxDataObjectSimple : public wxDataObject
{
public:
    wxDataObjectSimple(const wxDataFormat& format = wxFormatInvalid);
    virtual bool GetDataHere(void* buf) const;
    virtual size_t GetDataSize() const;
    const wxDataFormat& GetFormat() const;
    virtual bool SetData(size_t len, const void* buf);
    void SetFormat(const wxDataFormat& format);
};
class wxCustomDataObject : public wxDataObjectSimple
{
public:
    wxCustomDataObject(const wxDataFormat& format = wxFormatInvalid);
    virtual ~wxCustomDataObject();
    virtual void* Alloc(size_t size);
    virtual void Free();
    virtual void* GetData() const;
    virtual size_t GetSize() const;
    virtual bool SetData(size_t size, const void* data);
    void TakeData(size_t size, void* data);
};
class wxBitmapDataObject : public wxDataObjectSimple
{
public:
    wxBitmapDataObject(const wxBitmap& bitmap = wxNullBitmap);
    virtual wxBitmap GetBitmap() const;
    virtual void SetBitmap(const wxBitmap& bitmap);
};
class wxTextDataObject : public wxDataObjectSimple
{
public:
    wxTextDataObject(const wxString& text = wxEmptyString);
    virtual wxString GetText() const;
    virtual size_t GetTextLength() const;
    virtual size_t GetFormatCount(wxDataObject::Direction dir = wxDataObject::Get) const;
    const wxDataFormat& GetFormat() const;
    virtual void GetAllFormats(wxDataFormat* formats,
                               wxDataObject::Direction dir = wxDataObject::Get) const;
    virtual void SetText(const wxString& strText);
};
class wxURLDataObject: public wxTextDataObject
{
public:
    wxURLDataObject(const wxString& url = wxEmptyString);
    wxString GetURL() const;
    void SetURL(const wxString& url);
};
class wxFileDataObject : public wxDataObjectSimple
{
public:
    wxFileDataObject();
    void AddFile(const wxString& file);
    const wxArrayString& GetFilenames() const;
};
class wxHTMLDataObject : public wxDataObjectSimple
{
public:
    wxHTMLDataObject(const wxString& html = wxEmptyString);
    virtual wxString GetHTML() const;
    virtual void SetHTML(const wxString& html);
};