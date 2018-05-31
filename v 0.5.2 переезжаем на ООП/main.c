char *getVideoAddr(void);
void drowLineLow(int x1,int y1,int x2,int y2,int color);
void drowBackGround(int color);
void setPixel(int x,int y,int color);
int abs(int a);
void drowLineHigh(int x0,int y0,int x1,int y1,int color);
void drowLine(int x0,int y0,int x1,int y1,int color);
void drowCircle(int R,int x1,int y1,int color);
void drowSquare(int x0,int y0,int x1,int y1,int color);
int drowChar(int x,int y,int color, int multiplayer, char letter );
void drowString(char *message,int x,int y,int color,int multiplayer,int offset);

char *videoAddr;





int _start(){
	videoAddr=getVideoAddr();
	/*abcdefghijk*/
	/*lmnopqrstuwxyz*/
	char message[255]="hello world!!111!!!!\nabcde\nhello... dot. common,\nfghijklmnopqrstuwxyz\nhello my dear friend qwertyuiop[]asdfghjkl;'zxcvbnm,./' this is wery long text or not i don't cnow 0123456789 max width?\n";
	drowString(message,10,10,0xffffff,2,4);
	char message2[255]=";;;_-+=()!?.,;:";
	drowString(message2,10,510,0xffffff,1,1);

	/*for (int i=20;i<50;i++){
		drowCircle(i,500,500,0xff0000);
	}*/
	drowChar(900,400,0xff00ff,3,'2');

/*
	int x = 0;
	int y =0;
	int velosity=0;
	int flag = 0;
	char test =videoAddr;
	
	while(1){

		drowBackGround(0x8320a4);
		drowSquare(x+velosity,y+velosity,x+200+velosity,y+200+velosity,0x00ffff);

		velosity+=5;

		for(int i=0;i<1000;i++){
			for(int j=0;j<10000;j++);
		}
	}
*/


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

int abs(int a){ //абсолютное значение
	if (a>0){
		return a;
	}
	return -a;

}

void drowCircle(int R,int x1,int y1,int color){ //отрисовка круга
	int x = 0;
	int y = R;
	int delta = 1-2*R;
	int error =0;
	while (y>=0){
		setPixel(x1+x,y1+y,color);
		setPixel(x1+x,y1-y,color);
		setPixel(x1-x,y1+y,color);
		setPixel(x1-x,y1-y,color);
		error = 2 * (delta + y) -1;
		if((delta<0)&&(error<=0)){
			delta+=2*++x+1;
			continue;
		}
		error = 2*(delta - x) -1;
		if ((delta>0)&&(error>0)){
			delta += 1 -2*--y;
			continue;
		}
		x++;
		delta += 2*(x-y);
		y--;
	}
}


void drowLineLow(int x0,int y0,int x1,int y1,int color){ //рисуем линию в низ влево
	int dx = x1-x0;
	int dy = y1-y0;
	int yi = 1;
	if (dy<0){
		yi = -1;
		dy = -dy;
	}
	int D = 2*dy-dx;
	int y = y0;

	for (int x=x0;x<x1;x++){ //рисуем линию в низ вправо
		setPixel(x,y,color);
		if (D>0){
			y+=yi;
			D-=2*dx;
		}
		D+=2*dy;
	}
}

void drowLineHigh(int x0,int y0,int x1,int y1,int color){
	int dx = x1-x0;
	int dy = y1-y0;
	int xi = 1;
	if (dx<0){
		xi = -1;
		dx = -dx;
	}
	int D = 2*dx -dy;
	int x = x0;

	for (int y = y0;y<y1;y++){
		setPixel(x,y,color);
		if (D>0){
			x+=xi;
			D-=2*dy;
		}
		D+=2*dx;
	}
	
}

void drowLine(int x0, int y0, int x1, int y1,int color){ //рисует линию по алгоритму
	if (abs(y1-y0) <abs(x1-x0)){
		if (x0 > x1){
			drowLineLow(x1,y1,x0,y0,color);
		} else{
			drowLineLow(x0,y0,x1,y1,color);
		}
	}else{
		if (y0 > y1){
			drowLineHigh(x1,y1,x0,y0,color);
		} else {
			drowLineHigh(x0,y0,x1,y1,color);
		}
	}
}


void drowSquare(int x0,int y0,int x1,int y1,int color){ //ресует квадрат
	for (int y=y0;y<y1;y++){
		for (int x=x0;x<x1;x++){
			setPixel(x,y,color);
		}
	}
}

void drowBackGround(int color){ // градиент следует перерабоать
	int i,j,defoltColor;
	defoltColor=color;
	for (i=0;i<768;i++){
		for (j=0;j<1024;j++){
			setPixel(j,i,color);
			if (!(j%5)){
				color+=0x000100;
				}
		}
		color=defoltColor;
	}
}

void stopForSeckPlz(){ //как же всё быстро отрисовываеться, пожайлуста помедленее!
	for(int i=0;i<10000;i++){
		for(int j=0;j<1000;j++);
	}
}

void drowString(char *message,int x,int y,int color,int multiplayer,int offset){
	int i=0;
	int startx=x;
	while (message[i]){ 
		if (message[i]==' '){//отработка пробела
			x += (5*multiplayer) + offset;
			i++;
			continue;
		}
		if (message[i]=='\n'){ //отраюота переноса строки
			x=startx;
			y+=offset+(multiplayer*7);
			i++;
			continue;
		}
		if ((x + (5*multiplayer) + offset)>1024){
			x=startx;
			y+=offset+(multiplayer*7);
		}
		drowChar(x,y,color,multiplayer,message[i]);
		x += (5*multiplayer) + offset; //позиция для следующей буквы
		i++;
		//stopForSeckPlz();
	}
}
int drowChar(int x,int y,int color, int multiplayer, char letter ){

	int a[7][5] ={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1}};

	int b[7][5]={
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,0}};

	int c[7][5]={
	{0,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{0,1,1,1,1}};

	int d[7][5]={
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,0}};

	int e[7][5]={
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1}};

	int f[7][5]={
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0}};

	int g[7][5]={
	{0,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int h[7][5]={
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1}};

	int li[7][5]={
	{0,0,1,0,0},
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}};

	int lj[7][5]={
	{0,0,0,1,0},
	{0,0,0,0,0},
	{0,0,0,1,0},
	{0,0,0,1,0},
	{0,0,0,1,0},
	{0,0,0,1,0},
	{0,1,1,0,0}};

	int k[7][5]={
	{1,0,0,0,1},
	{1,0,0,1,0},
	{1,0,1,0,0},
	{1,1,0,0,0},
	{1,0,1,0,0},
	{1,0,0,1,0},
	{1,0,0,0,1}};

	int l[7][5]={
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1}};

	int m[7][5]={
	{1,1,0,1,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1}};

	int n[7][5]={
	{1,0,0,0,1},
	{1,1,0,0,1},
	{1,1,0,0,1},
	{1,0,1,0,1},
	{1,0,0,1,1},
	{1,0,0,1,1},
	{1,0,0,0,1}};

	int o[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int p[7][5]={
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,0},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,0,0,0,0}};

	int q[7][5]={
	{0,1,1,0,1},
	{1,0,0,1,1},
	{1,0,0,1,1},
	{0,1,1,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1}};

	int r[7][5]={
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,0},
	{1,0,1,0,0},
	{1,0,0,1,0},
	{1,0,0,0,1}};

	int s[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,0},
	{0,1,1,1,0},
	{0,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int t[7][5]={
	{1,1,1,1,1},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}};

	int u[7][5]={
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int v[7][5]={
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,0,1,0},
	{0,1,0,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0}};

	int w[7][5]={
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{0,1,0,1,0}};

	int lx[7][5]={
	{1,0,0,0,1},
	{0,1,0,1,0},
	{0,1,0,1,0},
	{0,0,1,0,0},
	{0,1,0,1,0},
	{0,1,0,1,0},
	{1,0,0,0,1}};

	int ly[7][5]={
	{1,0,0,0,1},
	{0,1,0,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}};


	int z[7][5]={
	{1,1,1,1,1},
	{0,0,0,0,1},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,1,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1}};

	int n0[7][5]={
	{0,1,1,1,0},
	{1,0,0,1,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,1,0,0,1},
	{0,1,1,1,0}};

	int n1[7][5]={
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1}};

	int n2[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,1,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1}};

	int n3[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{0,0,0,0,1},
	{0,1,1,1,0},
	{0,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int n4[7][5]={
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1}};

	int n5[7][5]={
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,0},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{1,1,1,1,0}};

	int n6[7][5]={
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,0,0,0,0},
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1}};

	int n7[7][5]={
	{1,1,1,1,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,0,0,0,1}};

	int n8[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0}};

	int n9[7][5]={
	{0,1,1,1,0},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{0,1,1,1,0},
	{0,0,0,0,1},
	{0,0,0,0,1},
	{0,1,1,1,0}};

//new

	int underLine[7][5]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{1,1,1,1,1}};

	int minus[7][5] ={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}};

	int plus[7][5]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}};

	int equal[7][5]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{1,1,1,1,1},
	{0,0,0,0,0},
	{1,1,1,1,1},
	{0,0,0,0,0},
	{0,0,0,0,0}};


	int leftBracket[7][5]={
	{0,0,0,0,1},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,1,0},
	{0,0,0,0,1}};

	int rightBracket[7][5]={
	{1,0,0,0,0},
	{0,1,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,1,0,0,0},
	{1,0,0,0,0}};

	int exclamationPoint[7][5]={
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
	{0,0,1,0,0}};

	int questionPoint[7][5]={
	{0,0,1,0,0},
	{0,1,0,1,0},
	{0,0,0,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0},
	{0,0,1,0,0}};

	int dot[7][5]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}};

	int comma[7][5]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,1,0,0}};

	int semicolon[7][5]={
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,1,0,0}};

	int colon[7][5]={
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}};

	int *printedLetter;

	/*switch(letter){
		case'a':printedLetter=*a; break;
		case'b':printedLetter=*b; break;
		case'c':printedLetter=*c; break;
		case'd':printedLetter=*d; break;
		case'e':printedLetter=*e; break;
		case'f':printedLetter=*f; break;
		case'g':printedLetter=*g; break;
		case'h':printedLetter=*h; break;
		case'i':printedLetter=*li; break;
		case'j':printedLetter=*lj; break;
		case'k':printedLetter=*k; break;
		case'l':printedLetter=*l; break;
		case'm':printedLetter=*m; break;
		case'n':printedLetter=*n; break;
		case'o':printedLetter=*o; break;
		case'p':printedLetter=*p; break;
		case'q':printedLetter=*q; break;
		case'r':printedLetter=*r; break;
		case's':printedLetter=*s; break;
		case't':printedLetter=*t; break;
		case'u':printedLetter=*u; break;
		case'v':printedLetter=*v; break;
		case'w':printedLetter=*w; break;
		case'x':printedLetter=*lx; break;
		case'y':printedLetter=*ly; break;
		case'z':printedLetter=*z; break;
		case'0':printedLetter=*n0; break;
		case'1':printedLetter=*n1; break;
		case'2':printedLetter=*n2; break;
		case'3':printedLetter=*n3; break;
		case'4':printedLetter=*n4; break;
		case'5':printedLetter=*n5; break;
		case'6':printedLetter=*n6; break;
		case'7':printedLetter=*n7; break;
		case'8':printedLetter=*n8; break;
		case'9':printedLetter=*n9; break;
	}*/

	if (letter == 'a'){
		printedLetter=*a;
	} else if (letter == 'b'){
		printedLetter=*b;
	} else if (letter == 'c'){
		printedLetter=*c;
	} else if (letter == 'd'){
		printedLetter=*d;
	} else if (letter == 'e'){
		printedLetter=*e;
	} else if (letter == 'f'){
		printedLetter=*f;
	} else if (letter == 'g'){
		printedLetter=*g;
	} else if (letter == 'h'){
		printedLetter=*h;
	} else if (letter == 'i'){
		printedLetter=*li;
	} else if (letter == 'j'){
		printedLetter=*lj;
	} else if (letter == 'k'){
		printedLetter=*k;
	} else if (letter == 'l'){
		printedLetter=*l;
	} else if (letter == 'm'){
		printedLetter=*m;
	} else if (letter == 'n'){
		printedLetter=*n;
	} else if (letter == 'o'){
		printedLetter=*o;
	} else if (letter == 'p'){
		printedLetter=*p;
	} else if (letter == 'q'){
		printedLetter=*q;
	} else if (letter == 'r'){
		printedLetter=*r;
	} else if (letter == 's'){
		printedLetter=*s;
	} else if (letter == 't'){
		printedLetter=*t;
	} else if (letter == 'u'){
		printedLetter=*u;
	} else if (letter == 'v'){
		printedLetter=*v;
	} else if (letter == 'w'){
		printedLetter=*w;
	} else if (letter == 'x'){
		printedLetter=*lx;
	} else if (letter == 'y'){
		printedLetter=*ly;
	} else if (letter == 'z'){
		printedLetter=*z;
	} else if (letter == '0'){
		printedLetter=*n0;
	} else if (letter == '1'){
		printedLetter=*n1;
	} else if (letter == '2'){
		printedLetter=*n2;
	} else if (letter == '3'){
		printedLetter=*n3;
	} else if (letter == '4'){
		printedLetter=*n4;
	} else if (letter == '5'){
		printedLetter=*n5;
	} else if (letter == '6'){
		printedLetter=*n6;
	} else if (letter == '7'){
		printedLetter=*n7;
	} else if (letter == '8'){
		printedLetter=*n8;
	} else if (letter == '9'){
		printedLetter=*n9;
	} else if (letter == '_'){ //new
		printedLetter=*underLine;
	} else if (letter == '-'){
		printedLetter=*minus;
	} else if (letter == '+'){
		printedLetter=*plus;
	} else if (letter == '='){
		printedLetter=*equal;
	} else if (letter == '('){
		printedLetter=*leftBracket;
	} else if (letter == ')'){
		printedLetter=*rightBracket;
	} else if (letter == '!'){
		printedLetter=*exclamationPoint;
	} else if (letter == '?'){
		printedLetter=*questionPoint;
	} else if (letter == '.'){
		printedLetter=*dot;
	} else if (letter == ','){
		printedLetter=*comma;
	} else if (letter == ';'){
		printedLetter=*semicolon;
	} else if (letter == ':'){
		printedLetter=*colon;
	} 
	//if no leter
	else{
		return 1;
	}

	for(int i=0;i<7;i++)	{
		for(int j=0;j<5;j++){
			if(printedLetter[j+i*5]){
				drowSquare(x+j*multiplayer,y+i*multiplayer,x+j*multiplayer+multiplayer,y+i*multiplayer+multiplayer,color);
			}
		}
	}
	return 0;
}

