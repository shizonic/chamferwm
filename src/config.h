#ifndef CONFIG_H
#define CONFIG_H

#include <boost/python.hpp>

namespace Backend{
class BackendKeyBinder;
class X11KeyBinder;
}

namespace WManager{
class Client;
class Container;
}

namespace Config{

class ContainerInterface{
public:
	ContainerInterface();
	virtual ~ContainerInterface();
	void CopySettingsSetup(WManager::Container::Setup &);
	void CopySettingsContainer();
	virtual void OnSetupContainer();
	virtual void OnSetupClient();
	virtual boost::python::object OnParent();
	virtual void OnCreate();
	enum PROPERTY_ID{
		PROPERTY_ID_NAME,
		PROPERTY_ID_CLASS
	};
	virtual bool OnFullscreen(bool);
	virtual void OnPropertyChange(PROPERTY_ID);
	boost::python::object GetNext() const;
	boost::python::object GetPrev() const;
	boost::python::object GetParent() const;
	boost::python::object GetFocus() const;
	boost::python::object GetFloatFocus() const;
	boost::python::object GetAdjacent(WManager::Container::ADJACENT) const;
	void Move(boost::python::object);
//public:
	boost::python::tuple canvasOffset;
	boost::python::tuple canvasExtent;
	boost::python::tuple borderWidth;
	boost::python::tuple minSize;
	boost::python::tuple maxSize;
	enum FLOAT{
		FLOAT_AUTOMATIC,
		FLOAT_ALWAYS,
		FLOAT_NEVER
	} floatingMode;
	//bool fullscreen;

	std::string wm_name;
	std::string wm_class;

	std::string vertexShader;
	std::string geometryShader;
	std::string fragmentShader;

	WManager::Container *pcontainer;
	boost::python::object self;
};

class ContainerProxy : public ContainerInterface, public boost::python::wrapper<ContainerInterface>{
public:
	ContainerProxy();
	~ContainerProxy();
	void OnSetupContainer();
	void OnSetupClient();
	boost::python::object OnParent();
	void OnCreate();
	bool OnFullscreen(bool);
	void OnPropertyChange(PROPERTY_ID);
};

class ContainerConfig{
public:
	ContainerConfig(ContainerInterface *, class Backend::X11Backend *);
	ContainerConfig(class Backend::X11Backend *);
	virtual ~ContainerConfig();
	ContainerInterface *pcontainerInt;
	class Backend::X11Backend *pbackend;
};

/*template<typename T>
class BackendContainerConfig : public T, public ContainerConfig{
public:
	BackendContainerConfig(ContainerInterface *, WManager::Container *, const WManager::Container::Setup &, class Backend::X11Backend *);
	BackendContainerConfig(class Backend::X11Backend *);
	~BackendContainerConfig();
};*/

class X11ContainerConfig : public Backend::X11Container, public ContainerConfig{
public:
	X11ContainerConfig(ContainerInterface *, WManager::Container *, const WManager::Container::Setup &, class Backend::X11Backend *);
	X11ContainerConfig(class Backend::X11Backend *);
	~X11ContainerConfig();
};

class DebugContainerConfig : public Backend::DebugContainer, public ContainerConfig{
public:
	DebugContainerConfig(ContainerInterface *, WManager::Container *, const WManager::Container::Setup &, class Backend::X11Backend *);
	DebugContainerConfig(class Backend::X11Backend *);
	~DebugContainerConfig();
};

class BackendInterface{
public:
	BackendInterface();
	virtual ~BackendInterface();
	virtual void OnSetupKeys(Backend::X11KeyBinder *, bool);
	virtual boost::python::object OnCreateContainer();
	virtual void OnKeyPress(uint);
	virtual void OnKeyRelease(uint);
	virtual void OnTimer();

	static void Bind(boost::python::object);
	static void SetFocus(WManager::Container *);
	static boost::python::object GetFocus();
	static boost::python::object GetRoot();
	//static void ResetFocus();

	static BackendInterface defaultInt;
	static BackendInterface *pbackendInt;
	static WManager::Container *pfocus; //client focus, managed by Python
	static std::deque<WManager::Container *> floatFocusQueue;
};

class BackendProxy : public BackendInterface, public boost::python::wrapper<BackendInterface>{
public:
	BackendProxy();
	~BackendProxy();
	//
	void OnSetupKeys(Backend::X11KeyBinder *, bool);
	boost::python::object OnCreateContainer();
	void OnKeyPress(uint);
	void OnKeyRelease(uint);
	void OnTimer();
};

class CompositorInterface{
public:
	CompositorInterface();
	~CompositorInterface();
	std::string shaderPath;
	//virtual void SetupShaders();

	static void Bind(boost::python::object);
	static CompositorInterface defaultInt;
	static CompositorInterface *pcompositorInt;
};

class CompositorProxy : public CompositorInterface, public boost::python::wrapper<CompositorInterface>{
public:
	CompositorProxy();
	~CompositorProxy();
};

class Loader{
public:
	Loader(const char *);
	~Loader();
	void Run(const char *, const char *);
};

}

#endif

