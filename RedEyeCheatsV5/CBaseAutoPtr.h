#pragma once
class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};
typedef void m_pObject;
template <class T>
class CBaseAutoPtr
{
public:
	CBaseAutoPtr() : m_pObject(0) {}
	CBaseAutoPtr(T* pFrom) : m_pObject(pFrom) {}

	operator const void* () const { return m_pObject; }
	operator void* () { return m_pObject; }

	operator const T* () const { return m_pObject; }
	operator const T* () { return m_pObject; }
	operator T* () { return m_pObject; }

	int			operator=(int i) { m_pObject = 0; return 0; }
	T* operator=(T* p) { m_pObject = p; return p; }

	bool        operator !() const { return (!m_pObject); }
	bool        operator!=(int i) const { return (m_pObject != NULL); }
	bool		operator==(const void* p) const { return (m_pObject == p); }
	bool		operator!=(const void* p) const { return (m_pObject != p); }
	bool		operator==(T* p) const { return operator==((void*)p); }
	bool		operator!=(T* p) const { return operator!=((void*)p); }
	bool		operator==(const CBaseAutoPtr<T>& p) const { return operator==((const void*)p); }
	bool		operator!=(const CBaseAutoPtr<T>& p) const { return operator!=((const void*)p); }

	T* operator->() { return m_pObject; }
	T& operator *() { return *m_pObject; }
	T** operator &() { return &m_pObject; }

	const T* operator->() const { return m_pObject; }
	const T& operator *() const { return *m_pObject; }
	T* const* operator &() const { return &m_pObject; }

protected:
	CBaseAutoPtr(const CBaseAutoPtr<T>& from) : m_pObject(from.m_pObject) {}
	void operator=(const CBaseAutoPtr<T>& from) { m_pObject = from.m_pObject; }

	T* m_pObject;
};

//---------------------------------------------------------

template <class T>
class CRefPtr : public CBaseAutoPtr<T>
{
	typedef CBaseAutoPtr<T> BaseClass;
public:
	CRefPtr() {}
	CRefPtr(T* pInit) : BaseClass(pInit) {}
	CRefPtr(const CRefPtr<T>& from) : BaseClass(from) {}
	~CRefPtr() { if (BaseClass::m_pObject) BaseClass::m_pObject->Release(); }

	void operator=(const CRefPtr<T>& from) { BaseClass::operator=(from); }

	int operator=(int i) { return BaseClass::operator=(i); }
	T* operator=(T* p) { return BaseClass::operator=(p); }

	operator bool() const { return !BaseClass::operator!(); }
	operator bool() { return !BaseClass::operator!(); }

	void SafeRelease() { if (BaseClass::m_pObject) BaseClass::m_pObject->Release(); BaseClass::m_pObject = 0; }
	void AssignAddRef(T* pFrom) { SafeRelease(); if (pFrom) pFrom->AddRef(); BaseClass::m_pObject = pFrom; }
	void AddRefAssignTo(T*& pTo) { ::SafeRelease(pTo); if (BaseClass::m_pObject) BaseClass::m_pObject->AddRef(); pTo = BaseClass::m_pObject; }
};
