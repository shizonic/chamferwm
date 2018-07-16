#ifndef CONTAINER_H
#define CONTAINER_H

namespace WManager{

class Client{
public:
	//Client(class BackendInterface *);
	Client();
	virtual ~Client();
	//
	//virtual functions for the backend implementation
	//SetTranslation
	//SetLayer
};

class Container{
public:
	Container(); //root container
	Container(Container *);
	~Container();
	//
	Container *pch; //First children
	Container *pnext; //Subsequent container in the parent container
	Client *pclient;

	//float wscale, hscale;
	// = 1.0f: default size, scale with the number of containers
	// < 1.0f: smaller than default, leaving the unscaled parallel containers more space
	
	/*enum{
		MODE_VSPLIT,
		MODE_HSPLIT,
		MODE_STACKED,
	} mode;*/
};

}


#endif

