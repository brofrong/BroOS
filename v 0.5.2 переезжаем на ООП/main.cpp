class screen
{
public:
	 screen(){
	 	videoAddres = *(char**)(0x8000);
	 	dataAddres = *(char**) (0x8004);
	 }
	~ screen(){}
	clearScrean(int color){
		for 
	}
private:
	char *videoAddres;
	char *dataAddres;
	void setPixel(int x,int y,int color){
		char *p;
		p=videoAddres;
		p+=((y*1024)+x)*3;
		*(int*)p=color;
	}
};

class window
{
public:
	window();
	~window();
	
};


int _start(){
	screen myscreen;
	myscreen.clearScrean(0xff0000);
	while(1);
}

char *getVideoAddr(void){ // один раз вызвать и больше не трогать
	char *p;
	asm ("mov eax,dword ptr[0x8000]");
	asm ("mov dword ptr[ebp-4],eax");
	return p;
}

void setPixel(int x,int y,int color){
	char *p;
	p=videoAddr;
	p+=((y*1024)+x)*3;
	*(int*)p=color;
}