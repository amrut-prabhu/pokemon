//#define _WIN32_WINNT 0X500

#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<process.h>
#include <windows.h>  //for Sleep()
#include<conio.h>	//for _getch()

using namespace sf;
using namespace std;

struct attacks
{
	char attname[25],pic[30];
	int attpow;
	int style;
};

struct info
{
	char a[3], d[3];
	char name[15], height[7], weight[10];
	char moves[4][15], des[4][65];	//description
	char category[10];
};

class character
{
	public:
		char chF[36], chB[36], chL[36], chR[36];
		int x, y;
		character()
		{
			x = 10;
			y = 300;
		}
		void reset()
		{
			x = 10;
			y = 300;
		}
		void copy(char ch1[36], char ch2[36], char ch3[36], char ch4[36])
		{
			strcpy_s(chF, ch1);
			strcpy_s(chB, ch2);
			strcpy_s(chL, ch3);
			strcpy_s(chR, ch4);
		}
};
 
class pokemon
{
	int att, def,speed;
	public:
		int hp,x,y,opp;		//opp=0 means pokemon is user		opp=1 means pokemon is opp		***used in attfunc() for fake out
		attacks a[4];
		char back[35],image[35],name[15],pic[35];	//pic[] is for pokedex
		pokemon()
		{
			hp = 100;
		}
		pokemon(int a, int d,int s, int o, char n[15], char pic[35], char backpic[35] = "\0")
		{
			att = a;
			def = d;
			speed = s;
			opp = o;
			hp = 100;
			strcpy_s(name, n);
			strcpy_s(image,pic);
			strcpy_s(back,backpic);
		}
		void reset(int a, int d, int s)	//To reset stats of wild pokemon
		{
			att = a;
			def = d;
			speed = s;
			hp = 100;
		}
		void display()
		{	
			cout << att << "\t" << def << "\t" << speed << "\t" << hp << "\t" << x << "\t" << y;
			for (int j = 0; j < 4; j++)
				cout << a[j].attname << "\t" << a[j].attpow << "\t" << a[j].style;
			cout << "\n";
		}
		void copy(char ch[35])
		{
			strcpy_s(pic,ch);
		}
		int getatt()
		{
			return(att);
		}
		int getdef()
		{
			return(def);
		}
		int getspd()
		{
			return(speed);
		}
		void incspd(int s)
		{
			speed += s;
		}
		void decspd(int s)
		{
			speed -= s;
		}
		void lowerspd()
		{
			speed -= 3;
		}
		void lowerdef(int l)
		{
			def -= l;
		}
		void loweratt(int l)
		{
			att -= l;
		}
		void incatt()
		{
			att += 4;
		}
		void incdef()
		{
			def += 4;
		}
};

void intro1();
void intro2();
void title();
void disp(int);
void pokedex();
void pokeinfo(int);
void choosech();
void choosepoke();
void game();
void fight(pokemon&,pokemon);
void attackfunc(pokemon&, pokemon&, int);
void result(pokemon&, pokemon&, int);
//void exitgame();

character c;
pokemon user;
pokemon Chikorita(20, 20,22, 0, "Chikorita", "pics\\Pokemon\\Chikorita.png","pics\\Pokemon\\Chikoritaback.png");
pokemon Charmander(20, 20, 22, 0, "Charmander", "pics\\Pokemon\\Charmander.png", "pics\\Pokemon\\Charmanderback.png");
pokemon Rattata(18, 18, 20, 1, "Rattata", "pics\\Pokemon\\Rattata.png");
pokemon Duskull(30, 25, 35, 1, "Duskull", "pics\\Pokemon\\Duskull.png");
pokemon Spearow(25, 20, 49, 1, "Spearow", "pics\\Pokemon\\Spearow.png");

int characterchoice = 1, pokechoice = 1, esc = 0;
int miss = 0;	//To check if fake out move was used
int toxic=0;	//To check if toxic move was used


int main()
{
	int te1[5], te3[5], te2[5];	//Temporary arrays of coordinates of wild pokemon
	attacks tempatt;
	char files[5][25] = { "Files\\Chikorita.dat", "Files\\Charamander.dat", "Files\\Rattata.dat", "Files\\Duskull.dat", "Files\\Spearow.dat" };

	///*
	//info i, k;
	//char nam[20] = "Files\\Info 5.dat";
	//char c[15];
	//fstream fstud(nam, ios::out);
	//cout << "\nPoke Name:  ";
	//cin >> i.name;
	//cout << "\nAttack: ";
	//cin >> i.a;
	//cout << "\nDefense:  ";
	//cin >> i.d;
	//cout << "\nHeight:  ";
	//cin >> i.height;
	//cout << "\nWeight:  ";
	//cin.getline(c, 14);
	//gets_s(i.weight);
	//cout << "\nCategory:  ";
	//cin.getline(c, 14);
	//gets_s(i.category);
	//for (int j = 0; j<4; j++)
	//{
	//	cout << "\n Move " << j + 1 << ":\t";
	//	cin.getline(c, 14);
	//	gets_s(i.moves[j]);
	//	cout << "Description\t";
	//	cin.getline(c, 14);
	//	gets_s(i.des[j]);
	//	cout << endl;
	//}
	//fstud.write((char*)&i, sizeof(i));
	//fstud.close();
	//cout << endl << endl << "----------------------------" << endl;
	//ifstream f(nam);
	//f.read((char*)&k, sizeof(k));
	//cout << k.name << "  " << k.a << " " << k.d << " " << k.height << " " << k.weight << " " << k.category << endl;
	//for (int j = 0; j<4; j++)
	//	cout << k.moves[j] << "  " << k.des[j] << endl;
	//f.close();*/
	

	srand (time(NULL));
	
	//Assigning pics for pokemon
	Chikorita.copy("pics\\Pokemon\\Chikorita.png");
	Charmander.copy("pics\\Pokemon\\Charmander.png");
	Rattata.copy("pics\\Pokemon\\Rattatapic.png");
	Duskull.copy("pics\\Pokemon\\Duskullpic.png");
	Spearow.copy("pics\\Pokemon\\Spearowpic.png");
	
	//Assigning positions for wild pokemon
	int okay = 1, okay1 = 0, okay2 = 0, okay3 = 0;	//okay1- coordinates of Rattata are correct, okay2-Duskull, okay3-Spearow
	while (okay==1)
	{
		///*int tempRattatax = random(0, 1550);
		//int tempRattatay = random(0, 982);
		//int tempDuskullx = random(0, 1550);
		//int tempDuskully = random(0, 982);
		//int tempSpearowx = random(0, 1550);
		//int tempSpearowy = random(0, 982);*/

		int tempRattatax = rand()%1550;		//Max permittable value of x coordinate  1550
		int tempRattatay = rand() % 982;	//Max permittable value of y coordinate  982
		int tempDuskullx = rand() % 1550;
		int tempDuskully = rand() % 982;
		int tempSpearowx = rand() % 1550;
		int tempSpearowy = rand() % 982;

		ifstream file("Files\\Pokepositions.txt");
		//Significance of numbers in file- 1.Left x coordinate 2.Right x coordinate 3.Top y coordinate 4.Bottom y coordinate 5.Separator(00001,00002 etc)
		while (!file.eof())
		{
			int coord[5], k = 0, n;
			while (k < 5)	//Assigning boundary of permittable coordinates to "coord[]"
			{
				file >> n;
				coord[k] = n;
				k++;
			}

			for (int i = 0; i < 3; i++)	//Rattata is assigned x and y, then Duskull, then Spearow
			{
				int x, y;
				switch (i)
				{
				case 0:
					x = tempRattatax;
					y = tempRattatay;
					break;
				case 1:	
					x = tempDuskullx;
					y = tempDuskully;
					break;
				case 2:	
					x = tempSpearowx;
					y = tempSpearowy;
					break;
				}
				if ((x >= coord[0]) && (x <= coord[1]) && (y >= coord[2]) && (y <= coord[3]))	//If the random value assigned is within the boundary
				{
					okay = 0;
					for (int t = 0; t < 1; t++)
					{
						if (okay1 == 0)
						{
							for (int z = 0; z < 5; z++)
								te1[z] = coord[z];
							Rattata.x = x;
							Rattata.y = y;
							okay1 = 1;	//Position is proper
							continue;
						}
						if (okay2 == 0)
						{
							for (int z = 0; z < 5; z++)
								te2[z] = coord[z];
							int a = abs(te2[4] - te1[4]);	//So that the pokemon are not located nearby
							if (a > 1)
							{
								Duskull.x = x;
								Duskull.y = y;
								okay2 = 1;  //Position is proper
							}
							continue;
						}
						if (okay3 == 0)
						{
							for (int z = 0; z < 5; z++)
								te3[z] = coord[z];
							int a1 = abs(te3[4] - te1[4]), a2 = abs(te3[4] - te2[4]);
							if (a1 > 1 && a2 > 1)	//So that the pokemon are not located nearby
							{
								Spearow.x = x;
								Spearow.y = y;
								okay3 = 1;   //Position is proper
							}
						}
					}
				}
				else		//If the random value assigned is not within the boundary
					okay = 1;	//Assign random values again (run loop again)
			}
		}
	}

	//for (int z = 0; z < 5; z++)
	//	cout<<te1[z]<<" ";
	//for (int z = 0; z < 5; z++)
	//	cout << te2[z] << " ";
	//for (int z = 0; z < 5; z++)
	//	cout << te3[z] << " ";
	//cout << endl;
	//cout << Rattata.x << "  " << Rattata.y << " " << te1[4]<<endl;
	//cout << Duskull.x << "  " << Duskull.y << " " << te2[4] << endl;
	//cout << Spearow.x << "  " << Spearow.y << " " << te3[4] << endl;
	cout << te1[4] << "    " << te2[4] << "    " << te3[4];

	//Assigning moves to pokemon from their respective files
	for (int i = 0; i < 5; i++)
	{
		fstream fstud(files[i], ios::in);
		for (int j = 0; j < 4; j++)
		{
			fstud.read((char*)&tempatt, sizeof(tempatt));
			switch (i)
			{
			case 0:
				Chikorita.a[j] = tempatt;
				break;
			case 1:
				Charmander.a[j] = tempatt;
				break;
			case 2:
				Rattata.a[j] = tempatt;
				break;
			case 3:
				Duskull.a[j] = tempatt;
				break;
			case 4:
				Spearow.a[j] = tempatt;
				break;
			}
		}
	}

	Sleep(500);
	system("cls");
	cout << "Press any key to continue...";
	//getc(stdin);
	_getch();
	//ShowWindow(GetConsoleWindow(), SW_HIDE);	//To hide console window
	//intro1();
	//intro2();
	//ShowWindow(GetConsoleWindow(), SW_RESTORE);		//To show console window
	

	

	RectangleShape background;
	background.setSize(sf::Vector2f(1537, 827));
	background.setFillColor(Color::Black);

	RenderWindow win(VideoMode(1537, 827), "Blank", Style::None);
	win.setPosition(sf::Vector2i(0, 0));
	//Clock clock; // starts the clock
	//int f = 0;

	/*while (win.isOpen())
	{
		Time elapsed = clock.getElapsedTime();
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
		}

		win.clear();
		win.draw(background);//background image
		win.display();     // end the current frame
		win.setActive(false);
		if (f==1)
			title();
		if (f==0)
			if (elapsed.asMilliseconds() > 3500)
			{
				//intro2();
				f = 1;
			}
			else if (elapsed.asMilliseconds() > 1000);
				//intro1();
	}*/

	//while (1)
	//{
	
	
	
	while (win.isOpen())
	{
		win.display();
		
		
		/*if (f == 0)
			 if (elapsed.asMilliseconds() > 1000);
			 {
			 f = 1;
			 intro1();
			 }
			 if (f == 1)
			 if (elapsed.asMilliseconds() > 2000)
			 {
			 f = 2;
			 intro2();
			 }
			 if (f == 2)
			 title();*/
		Music m;
		if (!m.openFromFile("intro.ogg"))
			return -1; // error
		//m.setPitch(1.5);
		if (m.getStatus() == 0)cout << " ";	//0-Stopped	2-Playing
		m.play();

		Sleep(1200);
		intro1();
		Sleep(1600);
		intro2();

		//Play Music
		Music music;
		if (!music.openFromFile("Pokemon Soundtrack.ogg"))
			return -1; // error
		m.stop();
		music.play();
		music.setLoop(true);	// it will restart playing from the beginning when it's finished
		win.setActive(false);
		title();
	}
	//}

	
	return 0;
}


void intro1()	
{
	RenderWindow window(VideoMode(370, 190), "Intro", Style::None);
	window.setPosition(sf::Vector2i(550, 300));

	//Pic
	RectangleShape pic;
	pic.setSize(sf::Vector2f(190, 175));	//260*240
	pic.setPosition(-15, 20);	//-28,-10
	char image[22] = "pics\\intro\\pic11.png";
	Texture img;

	//Logo
	RectangleShape logo;
	logo.setSize(sf::Vector2f(200, 180));
	logo.setPosition(170, 5);
	Texture l;
	if (l.loadFromFile("pics\\intro\\enigma.jpg") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	l.setSmooth(true);
	logo.setTexture(&l);

	Clock clock; // starts the clock

	while (window.isOpen())
	{
		Time elapsed = clock.getElapsedTime();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type==Event::Closed)
				window.close();
		}

		window.clear(Color(190,190,190,0));   //Grey(160,160,160) Background

		int t = elapsed.asMilliseconds();
		
		if (t > 1120 && t < 1190)
			strcpy_s(image, "pics\\intro\\pic22.png");
		else if (t > 1200 && t < 1500)
			strcpy_s(image, "pics\\intro\\pic33.png");
		else if (t > 1500 && t < 1600)
			strcpy_s(image, "pics\\intro\\pic11.png");

		if (t > 2700)
		{//clock.restart();
			window.setActive(false);
			window.close();
		}

		if (img.loadFromFile(image) == -1)
		{
			std::cout << "FAILED!!!" << "\n";
		}
		img.setSmooth(true);
		pic.setTexture(&img);
		
		window.draw(pic);

		window.draw(logo);

		window.display();
	}
}

void intro2()
{
	RenderWindow iwin(VideoMode(1537, 827), "Intro", Style::None);
	iwin.setPosition(sf::Vector2i(0, 0));	// change the position of the window (relatively to the desktop)

	iwin.setFramerateLimit(30);

	RectangleShape pic;
	pic.setSize(sf::Vector2f(2, 2));	//260*240
	pic.setPosition(600, 400);




	View view(FloatRect(0, 0, 1900, 800));
	//view.move(20, 0);
	iwin.setView(view);

	//Pic
	Sprite sprite;
	sprite.setPosition(580, 0);
	Texture texture;
	if (texture.loadFromFile("pics\\intro\\arcadefront1.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	sprite.setTexture(texture);


	/*RectangleShape pic;
	pic.setSize(Vector2f(800, 295));
	
	image.setSmooth(true);
	pic.setTexture(&image);*/


	Clock clock; // starts the clock

		
	while (iwin.isOpen())
	{
		Time elapsed = clock.getElapsedTime();

		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;
		//cout << x << " "<< y <<endl;

		/*if (time % 1500 > 1450)
		{
			size_x += 23;
			size_y += 55;
			pos_x -= 5;
			pos_y -= 20;
		}*/

		Event event;
		while (iwin.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				iwin.close();

		}
		iwin.clear();

	
			//sprite.scale(1.1f, 1.1f);
	
		//sprite.move(5, 5);
		int x1 = 280;
		int y1 = 440;
		//sprite.setOrigin(x1, y1);
		if (elapsed.asMilliseconds() > 1300)
		{
			view.zoom(0.97);
			//clock.restart();
			view.setCenter(880, 444);
		}
		if (elapsed.asMilliseconds() > 3900)
		{
			iwin.setActive(false);
			iwin.close();
		}
		iwin.setView(view);
		pic.setPosition(x1, y1);
		//pic.setPosition(pos_x, pos_y);
		//sprite.setSize(Vector2f(size_x, size_y));
		iwin.draw(sprite);
		//iwin.draw(pic);
		//cout << elapsed.asMilliseconds() << endl;

		iwin.display();     // end the current frame		
	}
}

void title()
{
	RenderWindow titlewin(VideoMode(1537, 827), "Pokémon Title Screen", Style::None);
	titlewin.setPosition(sf::Vector2i(0, 0));	// change the position of the window (relatively to the desktop)
	titlewin.setActive(true);
	/*HWND h;
	h=FindWindow(0, "Pokémon Title Screen");
	ShowWindow(h, SW_RESTORE);*/
	
	
	//Title
	RectangleShape text;
	text.setSize(sf::Vector2f(800, 295));
	sf::Texture textimage;
	if (textimage.loadFromFile("pics\\title.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	textimage.setSmooth(true);
	text.setTexture(&textimage);

	//Background image
	RectangleShape background;
	background.setSize(sf::Vector2f(1537, 827));
	sf::Texture image;
	if (image.loadFromFile("pics\\bckgrd.jpg") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	image.setSmooth(true);
	background.setTexture(&image);

	//Button for play
	RectangleShape but1;
	but1.setSize(sf::Vector2f(223, 78));
	but1.setFillColor(sf::Color::Red);
	but1.setOutlineThickness(3);
	but1.setOutlineColor(sf::Color(250, 150, 100));
	
	//Button for how to play
	RectangleShape but2;
	but2.setSize(sf::Vector2f(421, 76));
	but2.setFillColor(sf::Color::Red);
	but2.setOutlineThickness(3);
	but2.setOutlineColor(sf::Color(250, 150, 100));

	//Button for about
	RectangleShape but3;
	but3.setSize(sf::Vector2f(223, 70));
	but3.setFillColor(sf::Color::Red);
	but3.setOutlineThickness(3);
	but3.setOutlineColor(sf::Color(250, 150, 100));

	//Button for Pokedex
	RectangleShape but4;
	but4.setSize(sf::Vector2f(312, 73));
	but4.setFillColor(sf::Color::Red);
	but4.setOutlineThickness(3);
	but4.setOutlineColor(sf::Color(250, 150, 100));

	//Button for Exit
	RectangleShape but5;
	but5.setSize(sf::Vector2f(105, 55));
	but5.setFillColor(sf::Color::Yellow);
	but5.setPosition(1430, 770);

	Font font1;
	font1.loadFromFile("Fonts\\DESIB__.TTF");

	//"Play" text
	Text play;
	play.setFont(font1);
	play.setString("Play");
	play.setCharacterSize(80); 
	play.setColor(sf::Color::Black);

	//"How to play" text
	Text howto("How to Play", font1, 80);
	howto.setColor(sf::Color::Black);
	
	//"Pokédex" text
	Text pokede("Pokédex", font1, 80);
	pokede.setColor(sf::Color::Black);
	
	//"About" text
	Text about("About", font1, 80);
	about.setColor(sf::Color::Black);

	//"Exit" text
	Text ex("Exit", font1, 50);
	ex.setColor(sf::Color::Black);
	ex.setPosition(1440, 765);


	int temp1 = 0;

	while (titlewin.isOpen())
	{
		//cout << temp1++ << endl;
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;

		Event event;
		while (titlewin.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					titlewin.close();
					break;

				case sf::Event::MouseButtonPressed:
					switch (event.key.code)
					{
						case sf::Mouse::Left:
							if (x > 650 && x < 880 && y>375 && y < 465)
							{
								titlewin.close();
								choosech();
							}
							else if (x > 553 && x < 982 && y>495 && y < 578)
							{
								titlewin.close();
								disp(1);
							}
							else if (x > 610 && x < 930 && y>610 && y < 690)
							{
								titlewin.close();
								pokedex();
							}
							else if (x > 652 && x < 880 && y>728 && y < 801)
							{
								titlewin.close();
								disp(2);
							}
							else if (x > 1428 && x < 1540 && y>768 && y < 825)
								exit(0);
							break;
					}
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						//esc = 1;
						break;
					}
					break;
			}
		}
		titlewin.clear();


		titlewin.draw(background);//background image

		text.setPosition(350, 90);	
		titlewin.draw(text);	//"pokemon" title

		but1.setPosition(655, 380);//original position-(655, 470)
		titlewin.draw(but1);	//play button

		play.setPosition(693, 360);
		titlewin.draw(play);	//play text

		but2.setPosition(557, 500);	//(557,590)
		titlewin.draw(but2);	//how to play button

		howto.setPosition(560, 479);
		titlewin.draw(howto);	//how to play text

		but4.setPosition(613, 616);
		titlewin.draw(but4);	//pokedex button

		pokede.setPosition(615, 605);
		titlewin.draw(pokede);	//pokedex text
		
		but3.setPosition(655, 730);
		titlewin.draw(but3);	//about button

		about.setPosition(658, 715);
		titlewin.draw(about);	//about text
		
		titlewin.draw(but5);	//Exit button

		titlewin.draw(ex);	//Exit text

		//if (esc == 1)
		//{
			//titlewin.close();
			//exitgame(); 
		//}

		titlewin.display();     // end the current frame		
	}
}

void disp(int choice)	//1- how to play   2-About
{
	RenderWindow dispwin(VideoMode(1537, 827), "How To/About", Style::None);
	dispwin.setPosition(sf::Vector2i(0, 0));

	//Background image
	RectangleShape grass;
	grass.setSize(sf::Vector2f(45, 45));
	sf::Texture image;
	if (image.loadFromFile("pics\\grass.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	image.setSmooth(true);
	grass.setTexture(&image);
	grass.setPosition(295, 340);


	Font font1;
	font1.loadFromFile("Fonts\\GILLUBCD.TTF");

	//Title text
	char ch[15];
	int x, ty;		//x- position of title  ty- y position of object Text t
	if (choice == 1)
	{
		strcpy_s(ch, "How to Play");
		x = 385;
		ty = 750;
	}
	else
	{
		strcpy_s(ch, "About");
		x = 590;
		ty = 770;
	}
	Text top(ch, font1, 150);
	top.setStyle(Text::Underlined);
	top.setColor(sf::Color::Cyan);
	top.setPosition(x, 10);


	Font font2;
	font2.loadFromFile("Fonts\\david.ttf"); 

	//Instructions text
	Text howto[10];
	char str1[][95] = {"",
					  "- Select your avatar and Pokémon.",
					  "- Free roam on the map using the arrow keys.",
					  "- Wander in the         areas to attempt to find wild Pokémon to battle.",
					  "- Once the battle begins, use the arrow keys and press the enter key to choose your move.",
					  "- Be Careful. You can only use your special moves (displayed on the bottom row) twice.",
					  "- You win the battle if the opponent's HP reaches zero.",
					  "- You can check out the Pokédex to learn more about the Pokémon",
					  "- Press the escape key at any point to go back to the main menu.",
					  ""
					};
	for (int i = 0,y=170; i < 10; i++,y+=55)
	{
		howto[i].setFont(font2);
		howto[i].setString(str1[i]);
		howto[i].setCharacterSize(40);
		howto[i].setColor(sf::Color::Green);
		howto[i].setPosition(30, y);
	}

	//Title
	RectangleShape pok;
	pok.setSize(sf::Vector2f(350, 129));
	Texture textimage;
	if (textimage.loadFromFile("pics\\title.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	textimage.setSmooth(true);
	pok.setTexture(&textimage);		//Texture
	pok.setPosition(10, 190);

	//About Text
	Text about[10];
	char str2[][72] = { "Version: 5.0",
						"Programming language: C++",
						"External Library Used: Simple and Fast Multimedia Library (SFML 2.1)",
						"Programming by: Amrut Prabhu",
						"Special Thanks to:",
						"Mrs Lekshmi Sunil, Rahul Yadala, Aaron Sequeira, Akhil Dilip and others",
						""
					};
	for (int i = 0, y = 320; i < 7; i++, y += 70)
	{
		if (i == 4)
			y += 15;
		else if (i == 5)
			y -= 10;
		about[i].setFont(font2);
		about[i].setString(str2[i]);
		about[i].setCharacterSize(50);
		about[i].setColor(sf::Color::Green);
		about[i].setPosition(50, y);
	}


	Font font3;
	font3.loadFromFile("Fonts\\BRLNSR.TTF");

	Text t("Press Enter to go back.", font3, 40);
	t.setColor(sf::Color::White);
	t.setPosition(50, ty);

	while (dispwin.isOpen())
	{
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;
		//cout << x << " "<< y <<endl;

		Event event;
		while (dispwin.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				dispwin.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					dispwin.close();
					//if (choice == 1)
						//esc = 2;
					//else if (choice == 2)
						//esc = 3;
					//exitgame();
					title();
					break;

				case sf::Keyboard::Return:
					dispwin.close();
					title();
					break;
				}
				break;
			}
		}
		dispwin.clear();


		if (choice == 1)	//If how to play was selected
		{
			dispwin.draw(grass);	//grass image
			for (int i = 0; i < 10; i++)
				dispwin.draw(howto[i]);	//how to play text
		}

		else     //If about was selected
		{
			dispwin.draw(pok);
			for (int i = 0; i < 7; i++)
				dispwin.draw(about[i]);	//about text
		}

		dispwin.draw(top);	//heading text

		dispwin.draw(t);

		dispwin.display();     // end the current frame
	}
}

void pokedex()
{
	RenderWindow pokedex(VideoMode(1537, 827), "Pokédex", Style::None);
	pokedex.setPosition(sf::Vector2i(0, 0));

	//Heading
	RectangleShape titletext;
	titletext.setSize(sf::Vector2f(775, 305));
	sf::Texture image;
	if (image.loadFromFile("pics\\Pokedexlogo.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	image.setSmooth(true);
	titletext.setTexture(&image);		//Texture
	titletext.setPosition(360, -20);

	Font font1;
	font1.loadFromFile("Fonts\\BRLNSR.TTF");

	Text t("Press Enter to go back.", font1, 40);
	t.setColor(sf::Color::White);
	t.setPosition(50, 770);


	Font font2;
	font2.loadFromFile("Fonts\\GILLUBCD.TTF");

	//Pokemon names text
	Text names[6];
	char str[][12] = {  "Chikorita",
						"Charmander",
						"Rattata",
						"Spearow",
						"Duskull",
						""
	};
	for (int i = 0, y = 260; i < 6; i++, y += 95)
	{
		names[i].setFont(font2);
		names[i].setString(str[i]);
		names[i].setCharacterSize(70);
		names[i].setColor(sf::Color::Green);
		names[i].setPosition(50, y);
	}

	int choice;	//s.no. of pokemon selected

	while (pokedex.isOpen())
	{
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;
		//cout << x << " "<< y <<endl;

		Event event;
		while (pokedex.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				pokedex.close();
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (x > 47 && x < 330 && y>274 && y < 330)
					{
						pokedex.close();
						pokeinfo(1);
					}
					else if (x > 47 && x < 425 && y>368 && y < 430)
					{
						pokedex.close();
						pokeinfo(2);
					}
					else if (x > 47 && x < 275 && y>465 && y < 523)
					{
						pokedex.close();
						pokeinfo(3);
					}
					else if (x > 47 && x < 302 && y>560 && y < 628)
					{
						pokedex.close();
						pokeinfo(5);
					}
					else if (x > 47 && x < 275 && y>655 && y < 715)
					{
						pokedex.close();
						pokeinfo(4);
					}
					break;
				}
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					pokedex.close();
					title();
					break;

				case sf::Keyboard::Return:
					pokedex.close();
					title();
					break;
				}
				break;
			}
		}

		pokedex.clear();

		pokedex.draw(titletext);

		for (int i = 0; i < 6; i++)
			pokedex.draw(names[i]);	//pokemon names text
		
		pokedex.draw(t);

		pokedex.display();     // end the current frame
	}
}

void pokeinfo(int n)	//n- pokemon selected
{
	RenderWindow pokeinf(VideoMode(1537, 827), "Pokédex Info", Style::None);
	pokeinf.setPosition(sf::Vector2i(0, 0));
	
	pokemon p;


	info k;
	char file[30];
	switch (n)
	{
	case 1:
		p = Chikorita;
		strcpy_s(file, "Files\\Info 1.dat");
		break;
	case 2:
		p = Charmander;
		strcpy_s(file, "Files\\Info 2.dat");
		break;
	case 3:
		p = Rattata;
		strcpy_s(file, "Files\\Info 3.dat");
		break;
	case 4:
		p = Duskull;
		strcpy_s(file, "Files\\Info 4.dat");
		break;
	case 5:
		p = Spearow;
		strcpy_s(file, "Files\\Info 5.dat");
		break;
	}
	ifstream f(file);
	f.read((char*)&k, sizeof(k));
	cout << k.name << "  " << k.a << " " << k.d << " " << k.height << " " << k.weight << " " << k.category << endl;
	for (int j = 0; j<4; j++)
		cout << k.moves[j] << "  " << k.des[j] << endl;
	f.close();

	//Pokemon pic
	RectangleShape ppic;
	ppic.setSize(sf::Vector2f(500, 500));
	sf::Texture image;
	if (image.loadFromFile(p.pic) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	image.setSmooth(true);
	ppic.setTexture(&image);		//Texture
	ppic.setPosition(920, 10);
	
	Font font1;
	font1.loadFromFile("Fonts\\mvboli.ttf"); 
	//Pokemon name
	Text t(k.name, font1, 130);
	t.setColor(sf::Color::White);
	t.setStyle(Text::Bold);
	t.setPosition(20, -30);

	Font font2;
	font2.loadFromFile("Fonts\\david.ttf");
	//"Moves" text
	Text m("Moves", font2, 55);
	m.setColor(sf::Color::Green);
	m.setStyle(Text::Underlined);
	m.setPosition(30, 410);

	Font font3;
	font3.loadFromFile("Fonts\\BRLNSR.TTF");
	Font font4;
	font4.loadFromFile("Fonts\\ARLRDBD.TTF");
	char text[5][10] = { "Height:",
						 "Weight:",
						 "Category:",
						 "Attack:",
						 "Defense:"};
	//Pokemon basic info text
	Text basic[5],h[5];
	char str[5][15];
	strcpy_s(str[0], k.height);
	strcpy_s(str[1], k.weight);
	strcpy_s(str[2], k.category);
	strcpy_s(str[3], k.a);
	strcpy_s(str[4], k.d);	
	cout << k.a << k.category << k.d << k.weight << k.height << k.name;
	for (int j = 0; j<4; j++)
		cout << k.moves[j] << "  " << k.des[j] << endl;
	for (int i = 0, y=130; i < 5; i++,y+=55)
	{
		h[i].setFont(font4);
		h[i].setString(text[i]);
		h[i].setCharacterSize(40);
		h[i].setColor(Color(140, 210, 255, 255));
		h[i].setPosition(30, y);
		basic[i].setFont(font3);
		basic[i].setString(str[i]);
		basic[i].setCharacterSize(50);
		basic[i].setColor(sf::Color::Yellow);
		
	}
	basic[0].setPosition(175, 122);
	basic[1].setPosition(180, 175);
	basic[2].setPosition(225,233 );
	basic[3].setPosition(175,285);
	basic[4].setPosition(205, 340);
	
	
	//Move names and descriptions
	Text move[4], des[4];
	char mn[15], d[65];
	for (int i = 0, y = 485; i < 4; i++, y += 60)
	{
		strcpy_s(mn, k.moves[i]);
		strcpy_s(d, k.des[i]);

		move[i].setFont(font3);
		move[i].setString(mn);
		move[i].setCharacterSize(43);
		move[i].setColor(Color(140, 210, 255, 255));
		move[i].setPosition(30, y);

		des[i].setFont(font4);
		des[i].setString(d);
		des[i].setCharacterSize(40);
		des[i].setColor(sf::Color::Yellow);
	}
	des[0].setPosition(300, 490);
	des[1].setPosition(300, 550);
	des[2].setPosition(300, 610);
	des[3].setPosition(300, 670);
	


	/*//Move names and descriptions
	Text mname[4], moves[4];
	char mn[4][15], des[4][65];
	switch (n)
	{
	case 1:
		strcpy_s(mn[0],"Tail Whip");
		strcpy_s(mn[1], "Tackle");
		strcpy_s(mn[2], "Leech Seed");
		strcpy_s(mn[3], "Frenzy Plant");
		strcpy_s(des[0],"Decreases opponent defense");
		strcpy_s(des[1],"Decreases opponent HP");
		strcpy_s(des[2],"Decreases opponent HP and increases your HP");
		strcpy_s(des[3],"Decreases opponent HP");
		break;

	case 2:
		strcpy_s(mn[0], "Growl");
		strcpy_s(mn[1], "Scratch");
		strcpy_s(mn[2], "Fake Out");
		strcpy_s(mn[3], "Blast Burn");
		strcpy_s(des[0], "Decreases opponent attack strength");
		strcpy_s(des[1], "Decreases opponent HP");
		strcpy_s(des[2], "Opponent move misses twice");
		strcpy_s(des[3], "Decreases opponent HP");
		break;

	case 3:
		strcpy_s(mn[0], "Tackle");
		strcpy_s(mn[1], "Cut");
		strcpy_s(mn[2], "Growl");
		strcpy_s(mn[3], "Super Fang");
		strcpy_s(des[0], "Decreases opponent HP");
		strcpy_s(des[1], "Decreases opponent HP");
		strcpy_s(des[2], "Decreases opponent attack strength");
		strcpy_s(des[3], "Decreases opponent HP");
		break;

	case 4:
		strcpy_s(mn[0], "Payback");
		strcpy_s(mn[1], "Scary Face");
		strcpy_s(mn[2], "Shadow Sneak");
		strcpy_s(mn[3], "Ice Beam");
		strcpy_s(des[0], "Decreases opponent HP");
		strcpy_s(des[1], "Decreases opponent HP");
		strcpy_s(des[2], "Decreases opponent HP and decreases player speed");
		strcpy_s(des[3], "Decreases opponent HP");
		break;

	case 5:
		strcpy_s(mn[0], "Growl");
		strcpy_s(mn[1], "Tackle");
		strcpy_s(mn[2], "Toxic");
		strcpy_s(mn[3], "Drill Peck");
		strcpy_s(des[0], "Decreases opponent attack strength");
		strcpy_s(des[1], "Decreases opponent HP");
		strcpy_s(des[2], "Decreases opponent HP, inflicting more damage with every turn");
		strcpy_s(des[3], "Decreases opponent HP");
		break;
	}
	for (int i = 0, y = 485; i < 4; i++, y += 60)
	{
		mname[i].setFont(font3);
		mname[i].setString(mn[i]);
		mname[i].setCharacterSize(43);
		mname[i].setColor(sf::Color::Blue);
		mname[i].setPosition(30, y);

		moves[i].setFont(font4);
		moves[i].setString(des[i]);
		moves[i].setCharacterSize(40);
		moves[i].setColor(sf::Color::Yellow);
	}
	moves[0].setPosition(300, 490);
	moves[1].setPosition(300, 550);
	moves[2].setPosition(300, 610);
	moves[3].setPosition(300, 670);*/

	//Exit text
	Text e("Press Enter to go back.", font3, 35);
	e.setColor(Color::Magenta);
	e.setPosition(30, 760);


	while (pokeinf.isOpen())
	{

		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;
		//cout << x << " "<< y <<endl;

		Event event;
		while (pokeinf.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				pokeinf.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					pokeinf.close();
					//exitgame();
					title();
					break;

				case sf::Keyboard::Return:
					pokeinf.close();
					pokedex();
					break;
				}
				break;
			}
		}

		pokeinf.clear();

		for (int i = 0; i < 5; i++)
		{
			pokeinf.draw(h[i]);
			pokeinf.draw(basic[i]);
		}

		for (int i = 0; i < 4; i++)
		{
			pokeinf.draw(move[i]);
			pokeinf.draw(des[i]);
		}

		pokeinf.draw(ppic);	//Pokemon pic

		pokeinf.draw(t);	//Pokemon name

		pokeinf.draw(m);	//"Moves" Text

		pokeinf.draw(e);	//Exit text

		pokeinf.display();     // end the current frame
	}

}

void choosech()
{
	Mouse::setPosition(sf::Vector2i(769,60));

	RenderWindow choosewin(VideoMode(1537, 827), "Character Select", Style::None);
	choosewin.setPosition(sf::Vector2i(0, 0));

	RectangleShape dawn;
	sf::Texture dimage;
	if (dimage.loadFromFile("pics\\Dawn_pic.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	dimage.setSmooth(true);
	dawn.setTexture(&dimage);		

	RectangleShape lucas;
	sf::Texture limage;
	if (limage.loadFromFile("pics\\Lucas_pic.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	limage.setSmooth(true);
	lucas.setTexture(&limage);		

	RectangleShape colour1;
	colour1.setSize(sf::Vector2f(769, 800));
	colour1.setPosition(0, 75);	
	colour1.setFillColor(Color::Red);

	RectangleShape colour2;
	colour2.setSize(sf::Vector2f(769, 800));
	colour2.setPosition(769, 75);	
	colour2.setFillColor(Color::Blue);

	Font font1;
	font1.loadFromFile("Fonts\\DESIB__.TTF");

	//"Choose" text
	Text choose("Choose your Avatar", font1, 80);
	choose.setColor(sf::Color::White);

	Font font2;
	font2.loadFromFile("Fonts\\RAGE.TTF");

	Text dawntext("Dawn", font2, 130);
	dawntext.setColor(sf::Color::Green);
	dawntext.setStyle(sf::Text::Bold);

	Text lucastext("Lucas", font2, 140);
	lucastext.setColor(sf::Color::Green);
	lucastext.setStyle(sf::Text::Bold);

	while (choosewin.isOpen())
	{
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;

		int lpos_x = 940, lpos_y = 95, dpos_x = 315, dpos_y = 85;	//Initial positions of dawn and lucas pictures
		int lsize_x=288, lsize_y=700, dsize_x=292, dsize_y=711;	//Initial sizes of dawn and lucas pictures
		if (x > 0 && x < 769 && y>75 && y < 827)
		{
			dsize_x += 23;
			dsize_y += 55;
			dpos_x -= 5;
			dpos_y -= 20;
		}
		else if (x > 769 && x < 1537 && y>75 && y < 827)
		{
			lsize_x += 20;
			lsize_y += 49;
			lpos_x -= 5;
			lpos_y -= 18;
		}

		Event event;
		while (choosewin.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				choosewin.close();
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (x > 0 && x < 769 && y>65 && y < 827)
					{
						choosewin.close();
						characterchoice = 1;
						choosepoke();
					}
					else if (x > 769 && x < 1537 && y>65 && y < 827)
					{
						choosewin.close();
						characterchoice = 2;
						choosepoke();
					}
					break;
				}
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					choosewin.close();
					//esc = 4;
					title();
					break;
				}
				break;
			}
		}
		choosewin.clear();

		choosewin.draw(colour1);
		choosewin.draw(colour2);

		dawn.setSize(sf::Vector2f(dsize_x, dsize_y));
		dawn.setPosition(dpos_x, dpos_y);
		choosewin.draw(dawn);

		lucas.setSize(sf::Vector2f(lsize_x, lsize_y));
		lucas.setPosition(lpos_x, lpos_y);
		choosewin.draw(lucas);

		choose.setPosition(397, -23);
		choosewin.draw(choose);	//Choose text

		dawntext.setPosition(10, 70);
		choosewin.draw(dawntext);	//Dawn text

		lucastext.setPosition(1200, 70);
		choosewin.draw(lucastext);	//Lucas text

		choosewin.display();     // end the current frame
	}
}

void choosepoke()
{
	Mouse::setPosition(sf::Vector2i(769, 60));

	RenderWindow choosewin(VideoMode(1537, 827), "Pokémon Select", Style::None);
	choosewin.setPosition(sf::Vector2i(0, 0));	

	RectangleShape chikorita;
	sf::Texture dimage;
	if (dimage.loadFromFile("pics\\Pokemon\\Chikorita.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	dimage.setSmooth(true);
	chikorita.setTexture(&dimage);		

	RectangleShape charmander;
	sf::Texture limage;
	if (limage.loadFromFile("pics\\Pokemon\\Charmander.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	limage.setSmooth(true);
	charmander.setTexture(&limage);		

	RectangleShape colour1;
	colour1.setSize(sf::Vector2f(769, 795));
	colour1.setPosition(0, 85);	
	colour1.setFillColor(Color::Green);

	RectangleShape colour2;
	colour2.setSize(sf::Vector2f(769, 795));
	colour2.setPosition(769, 85);	
	colour2.setFillColor(Color::Red);

	Font font1;
	font1.loadFromFile("Fonts\\DESIB__.TTF");

	//"Choose" text
	Text choose("Choose your Pokémon", font1, 80);
	choose.setColor(sf::Color::White);

	Font font2;
	font2.loadFromFile("Fonts\\FREESCPT.TTF");

	Text chikoritatext("Chikorita", font2, 140);
	chikoritatext.setColor(sf::Color::Black);
	chikoritatext.setStyle(sf::Text::Bold);

	Text charmandertext("Charmander", font2, 147);
	charmandertext.setColor(sf::Color::Black);
	charmandertext.setStyle(sf::Text::Bold);

	while (choosewin.isOpen())
	{
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;

		int dpos_x = 200, dpos_y = 165, lpos_x = 870, lpos_y = 220;	//Initial positions of chikorita and charmander pictures
		int dsize_x = 510, dsize_y = 590, lsize_x = 488, lsize_y = 560;	//Initial sizes of chikorita and charmander pictures
		if (x > 0 && x < 769 && y>85 && y < 827)
		{
			dsize_x += 61;
			dsize_y += 80;
			dpos_x -= 10;
			dpos_y -= 55;
		}
		else if (x > 769 && x < 1537 && y>85 && y < 827)
		{
			lsize_x += 78;
			lsize_y += 90;
			lpos_x -= 35;
			lpos_y -= 70;
		}

		Event event;
		while (choosewin.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				choosewin.close();
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (x > 0 && x < 769 && y>85 && y < 827)
					{
						choosewin.close();
						pokechoice = 1;
						game();
					}
					else if (x > 769 && x < 1537 && y>85 && y < 827)
					{
						choosewin.close();
						pokechoice = 2;
						game();
					}
					break;
				}
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					choosewin.close();
					//esc = 5;
					title();
					break;
				}
				break;
			}
		}
		choosewin.clear();

		choosewin.draw(colour1);
		choosewin.draw(colour2);

		chikorita.setSize(sf::Vector2f(dsize_x, dsize_y));
		chikorita.setPosition(dpos_x, dpos_y);
		choosewin.draw(chikorita);

		charmander.setSize(sf::Vector2f(lsize_x, lsize_y));
		charmander.setPosition(lpos_x, lpos_y);
		choosewin.draw(charmander);

		choose.setPosition(397, -12);
		choosewin.draw(choose);	//Choose text

		chikoritatext.setPosition(40, 70);
		choosewin.draw(chikoritatext);	//chikorita text

		charmandertext.setPosition(1070, 70);
		choosewin.draw(charmandertext);	//charmander text

		choosewin.display(); 
	}
}

void game()
{
	RenderWindow window1(VideoMode(1902, 985), "Game");
	window1.setPosition(sf::Vector2i(0, 0));	
	window1.setMouseCursorVisible(false);		//hide mouse pointer in the game window

	//Map
	RectangleShape map;
	map.setSize(sf::Vector2f(1902, 985));	//size of each cell is (46,46)
	sf::Texture mapimage;
	if (mapimage.loadFromFile("pics\\1440x840.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	map.setTexture(&mapimage);	

	//Character sprites
	if (characterchoice == 1)
		c.copy("pics\\Dawn sprite\\dawnF.png", "pics\\Dawn sprite\\dawnB.png", "pics\\Dawn sprite\\dawnL.png", "pics\\Dawn sprite\\dawnR.png");
	else if (characterchoice == 2)
		c.copy("pics\\Lucas sprite\\lucasF.png", "pics\\Lucas sprite\\lucasB.png", "pics\\Lucas sprite\\lucasL.png", "pics\\Lucas sprite\\lucasR.png");
	
	if (pokechoice == 1)
		user = Chikorita;
	else if (pokechoice == 2)
		user = Charmander;
	user.display();
	//Character sprite
	RectangleShape cell;
	cell.setSize(sf::Vector2f(46, 46));
	sf::Texture cpic;
	if (cpic.loadFromFile(c.chF) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	cell.setTexture(&cpic);

	int f=0, fx=0,fy=0;	//variables to prevent repetition of fights    f: 0-fight can take place		fx,fy-position of user where fight occurs
	c.reset();	//resets player's original position

	while (window1.isOpen())
	{
		//cout << "Mouse position: x:" << ((sf::Mouse::getPosition(window1).x)) << endl;	//Displays mouse x position w.r.t. window
		//cout << "Mouse position: y:" << ((sf::Mouse::getPosition(window1).y)) << endl << endl;

		int type;

		Event event;
		while (window1.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window1.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window1.close();
					title();
					break;

				case sf::Keyboard::Left:
					cpic.loadFromFile(c.chL);
					c.x -= 59;
					type = 1;
					break;

				case sf::Keyboard::Right:
					cpic.loadFromFile(c.chR);
					c.x += 59;
					type = 2;
					break;

				case sf::Keyboard::Up:
					cpic.loadFromFile(c.chB);
					c.y -= 53;
					type = 3;
					break;

				case sf::Keyboard::Down:
					cpic.loadFromFile(c.chF);
					c.y += 53;
					type = 4;
					break;
				}
				break;
			}
		}
		window1.clear();

		if (esc == 1)	//If escape was pressed in result or fight window
		{
			esc = 0;
			window1.close();
			title();
		}

		map.setPosition(0, 0);
		window1.draw(map);

		if (fx != c.x || fy != c.y)
			f = 0;

		//If x or y coordinate is out of the window
		if (c.x < -2)
			c.x += 59;
		else if (c.y < -20)
			c.y += 53;
		else if (c.y > 975)
			c.y -= 53;


		ifstream file("Files\\Coordinates.txt");
		//Significance of numbers in file- 1.Left x coordinate 2.Right x coordinate 3.Top y coordinate 4.Bottom y coordinate 5.Separator(00000)
		int found = 0;
		while (!file.eof())
		{
			int coord[5], k = 0, n;
			while (k < 5)
			{
				file >> n;
				coord[k] = n;
				k++;
			}

			if ((c.x >= coord[0]) && (c.x <= coord[1]) && (c.y >= coord[2]) && (c.y <= coord[3]))
			{
				switch (type)
				{
				case 1:	c.x += 59;	//if left is pressed
					break;

				case 2:	c.x -= 59;	//if right is pressed
					break;

				case 3: c.y += 53;	//if up is pressed
					break;

				case 4: c.y -= 53;	//if down is pressed
					break;
				}
				cout << "no";
			}
		}
		cell.setPosition(c.x, c.y);
		window1.draw(cell);


		for (int i = 0; i < 3; i++)
		{
			int x, y;
			switch (i)
			{
			case 0:
				x = Rattata.x;
				y = Rattata.y;
				break;

			case 1:
				x = Duskull.x;
				y = Duskull.y;
				break;

			case 2:
				x = Spearow.x;
				y = Spearow.y;
				break;
			}

			if ((x >= c.x) && (x <= c.x + 59) && (y >= c.y) && (y <= c.y + 53))	//If wild pokemon is found
			{

				cout << "\n\n" << i;
				fx=c.x;
				fy=c.y;
				if (f == 0)
					switch (i)
					{
					case 0:
						f = 1;
						fight(user, Rattata);
						Rattata.reset(18, 18, 20);
						break;

					case 1:
						f = 1;
						fight(user, Duskull);
						Duskull.reset(30, 25, 35);
						break;

					case 2:
						f = 1;
						fight(user, Spearow);
						Spearow.reset(25, 20, 49);
						break;
					}
			}
		}

		window1.display();   // end the current frame
	}
}

void fight(pokemon& p,pokemon opp)
{
	p.hp = 100;
	RenderWindow fightwin(VideoMode(1537, 827), "Fight", Style::None);
	fightwin.setPosition(sf::Vector2i(0, 0));

	//window1.setMouseCursorVisible(false);	

	//Background image
	RectangleShape background(sf::Vector2f(1137, 629));
	background.setPosition(200, 0);
	sf::Texture bckgd;
	if (bckgd.loadFromFile("pics\\fight\\18502.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	background.setTexture(&bckgd);		

	//Text box
	RectangleShape box(sf::Vector2f(1137, 200));
	box.setPosition(200,625);
	sf::Texture boximage;
	if (boximage.loadFromFile("pics\\fight\\18507.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	box.setTexture(&boximage);	

	//Character
	char ch[30];
	if (characterchoice == 1)
		strcpy_s(ch, "pics\\Dawn sprite\\back.png");
	else if (characterchoice==2)
		strcpy_s(ch, "pics\\Lucas sprite\\back.png");
	RectangleShape character(sf::Vector2f(250, 270));
	character.setPosition(200, 360);
	sf::Texture chimage;
	if (chimage.loadFromFile(ch) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	character.setTexture(&chimage);		
	
	//My Pokemon
	RectangleShape pokem(sf::Vector2f(290, 240));
	pokem.setPosition(460, 390);
	sf::Texture pokimage;
	if (pokimage.loadFromFile(p.back) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	pokem.setTexture(&pokimage);		

	//Opponent
	RectangleShape oppon(sf::Vector2f(310, 368));
	oppon.setPosition(890, 80);
	sf::Texture oppimage;
	if (oppimage.loadFromFile(opp.image) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	oppon.setTexture(&oppimage);		

	//Opponent health bar
	RectangleShape opphealth(sf::Vector2f(550, 100));
	opphealth.setPosition(200, 65);
	sf::Texture ohimage;
	if (ohimage.loadFromFile("pics\\fight\\opp hp.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	opphealth.setTexture(&ohimage);		

	//User health bar
	RectangleShape health(sf::Vector2f(550, 100));
	health.setPosition(787, 489);
	sf::Texture himage;
	if (himage.loadFromFile("pics\\fight\\your hp.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	health.setTexture(&himage);		

	//User HP
	RectangleShape uhp;	//Health bar is 218 px long(895 to 1113), 7 px wide(558 to 565)
	uhp.setPosition(895, 558);
	float i = p.hp*2.18;	//size of health bar

	//Opponent HP
	RectangleShape ohp;	//Health bar is 218 px long(895 to 1113), 7 px wide(558 to 565)
	ohp.setPosition(425, 134);
	float j = 100*2.18;	//size of health bar

	//Pointer
	RectangleShape pointer(sf::Vector2f(40, 58));
	int x=250, y=655;	//x=250  y=655	x+=470	  y+=75
	sf::Texture pimage;
	if (pimage.loadFromFile("pics\\fight\\pointer.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	pointer.setTexture(&pimage);		

	//User Attack Graphic
	RectangleShape uattgra(sf::Vector2f(510, 400));
	uattgra.setPosition(827,0);	
	sf::Texture uatgr;
	char uattimage[35];

	//Poison pic
	RectangleShape psn(sf::Vector2f(60, 24));
	sf::Texture psnimage;
	if (psnimage.loadFromFile("pics\\fight\\psn.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	psn.setTexture(&psnimage);		
	psn.setPosition(1270,510);

	char oattimage[35];

	Font font1;
	font1.loadFromFile("Fonts\\ARLRDBD.TTF");

	//Move 1 text
	Text move1(p.a[0].attname, font1, 70);	
	move1.setColor(sf::Color::Black);
	move1.setPosition(295, 640);
	//Move 2 text
	Text move2(p.a[1].attname, font1, 70);	
	move2.setColor(sf::Color::Black);
	move2.setPosition(765, 640);
	//Move 3 text
	Text move3(p.a[2].attname, font1, 70);	
	move3.setColor(sf::Color::Black);
	move3.setPosition(295, 715);
	//Move 4 text
	Text move4(p.a[3].attname, font1, 70);	
	move4.setColor(sf::Color::Black);
	move4.setPosition(765, 715);

	Font font2;
	font2.loadFromFile("Fonts\\SFPixelate-Bold.ttf");
	//User Pokemon
	Text uname(p.name, font2, 45);	
	uname.setColor(sf::Color::Black);
	uname.setPosition(860, 495);
	//Opp Pokemon
	Text oppname(opp.name, font2, 45);	
	oppname.setColor(sf::Color::Black);
	oppname.setPosition(200, 70);
	cout << p.name;

	int a3 = 0, a4 = 0;		//No of times attack 3 and 4 are used
	int temp=1, turn = 1, oppturn, select;		//turn  0-PC's turn to attack, 1-User's turn to attack
	if (p.getspd() >= opp.getspd())
		turn = 1;
	else
	{
		turn = 0;
		oppturn = 0;
	}

	int att = 0;		//0-Opp chose attack  1- User chose an attack	3-Temp value  *****Used for appyling att graphic texture
	
	Clock clock; // starts the clock
	int t1 = 0;		//t1 is the time when attack is chosen
	int n = rand() % 3, num = 0;		//n- attack no. of opp chosen,   num- variable to make sure attfunc is only used by opp once

	while (fightwin.isOpen())
	{
		Time t = milliseconds(30);
		sleep(t);

		Time elapsed = clock.getElapsedTime();

		Event event;
		while (fightwin.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				fightwin.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					fightwin.close();
					esc = 1;
					break;

				case sf::Keyboard::Left:	//Moving pointer Left
					if (x > 700)
						x -= 470;
					break;
				case sf::Keyboard::Right:	//Moving pointer Right
					if (x < 700)
						x += 470;
					break;
				case sf::Keyboard::Up:		//Moving pointer Up
					if (y > 700)
						y -= 75;
					break;
				case sf::Keyboard::Down:	//Moving pointer Down
					if (y < 700)
						y += 75;
					break;

				case sf::Keyboard::Return:
					if (turn == 1)	//If it is user's turn to attack
						if (x == 250)
							if (y < 700)		//Top left corner attack chosen
							{
								t1 = elapsed.asMilliseconds();
								att = 1;
								cout << p.a[0].attname << "\t" << p.a[0].attpow << "\t" << p.a[0].style;
								strcpy_s(uattimage, p.a[0].pic);
								attackfunc(p, opp, 0);
								turn = 4;
							}
							else            //Top right corner attack chosen
							{
								a3++;
								if (a3 > 2)	//If move is used more than twice, no effect
									break;
								t1 = elapsed.asMilliseconds();
								att = 1;
								cout << p.a[2].attname << "\t" << p.a[2].attpow << "\t" << p.a[2].style;
								strcpy_s(uattimage, p.a[2].pic);
								attackfunc(p, opp, 2);
								turn = 4;
							}

						else
							if (y < 700)		//Bottom left corner attack chosen
							{
								t1 = elapsed.asMilliseconds();
								att = 1;
								cout << p.a[1].attname << "\t" << p.a[1].attpow << "\t" << p.a[1].style;
								strcpy_s(uattimage, p.a[1].pic);
								attackfunc(p, opp, 1);
								turn = 4;
							}
							else            //Bottom right corner attack chosen
							{
								a4++;
								if (a4 > 2)	//If move is used more than twice, no effect
									break;
								t1 = elapsed.asMilliseconds();
								att = 1;
								cout << p.a[3].attname << "\t" << p.a[3].attpow << "\t" << p.a[3].style;
								strcpy_s(uattimage, p.a[3].pic);
								cout << uattimage;
								attackfunc(p, opp, 3);
								turn = 4;
							}
				}
			}
		}
		
		//Random selection of opponent's move
		if (turn == 0 && temp==0)		
		{
			int temporary[4] = { 7, 5, 9, 6 };
			int m = 0, temp = rand() % 500;
			for (m = 0; m < 4; m++)
				if (temp % temporary[m] == 0)
					break;
				
			switch (m)
			{
			case 0:
				n = 0;
				break;
			case 1:
				n = 1;
				break;
			case 2:
				n = 2;
				break;
			case 3:
				n = 3;
				break;
			default:
				n = rand() % 3;
			}
			t1 = elapsed.asMilliseconds();
			strcpy_s(oattimage, opp.a[n].pic);
			select = 1;
			att = 0;
			turn = 3;
		}

		if (num == 0 && temp == 0 && oppturn == 0)
		{
			cout << oattimage;
			attackfunc(opp, p, n);
			num = 1;
		}

		//Setting user health for displaying
		if (i>70 * 2.18)		//Scale is 2.18
			uhp.setFillColor(Color::Green);
		else if (i>30 * 2.18)
			uhp.setFillColor(Color::Yellow);
		else if (i >= 02.18)
			uhp.setFillColor(Color::Red);
		else
			uhp.setFillColor(Color::Transparent);
		if (floor(i) == floor(p.hp*2.18));	//if the health bar has been filled up till the user's actual hp
		else if (i < p.hp*2.18)
			i += 2.18;
		else
			i -= 2.18;
		uhp.setSize(sf::Vector2f(i, 7));


		//Setting opp health for displaying
		if (j>70 * 2.18)		//Scale is 2.18
			ohp.setFillColor(Color::Green);
		else if (j>30 * 2.18)
			ohp.setFillColor(Color::Yellow);
		else if (j >= 02.18)
			ohp.setFillColor(Color::Red);
		else
			ohp.setFillColor(Color::Transparent);
		if (floor(j) == floor(opp.hp*2.18)); //if the health bar has been filled up till the opp's actual hp
		else
			j -= 2.18;
		ohp.setSize(sf::Vector2f(j, 7));


		fightwin.clear();

		fightwin.draw(box);	//Text box

		fightwin.draw(background);//background image

		fightwin.draw(character);	//Character image

		fightwin.draw(pokem);	//Pokemon image

		fightwin.draw(oppon);	//Opponent image

		fightwin.draw(health);	//User health bar

		fightwin.draw(uhp);

		if (toxic==1)
			fightwin.draw(psn);

		fightwin.draw(opphealth);	//Opponent health bar

		pointer.setPosition(x, y);
		fightwin.draw(pointer);		//Select pointer		


		if (elapsed.asMilliseconds() > 1000)	//Pause when window opens for 1 second
			temp = 0;


		if (att == 1)	//If attack was chosen by user
		{
			if (uatgr.loadFromFile(uattimage) == -1)
			{
				std::cout << "FAILED!!!" << "\n";
			}
			uattgra.setTexture(&uatgr);	
			fightwin.draw(uattgra);		//Attack Graphic
		}

		if(elapsed.asMilliseconds() - t1 <4500)
			if (att == 0 && temp == 0	&& oppturn==0 && select==1)	//If attack was chosen by opp
			{
				//Opponent Attack Graphic
				RectangleShape oattgra(sf::Vector2f(450, 280));
				oattgra.setPosition(400, 300);
				sf::Texture oatgr;
				strcpy_s(oattimage, opp.a[n].pic);
				if (oatgr.loadFromFile(oattimage) == -1)
				{
					std::cout << "FAILED!!!" << "\n";
				}
				oattgra.setTexture(&oatgr);		
				sf::Vector2f position = oattgra.getSize();
				fightwin.draw(oattgra);		//Attack Graphic
			}


		fightwin.draw(ohp);

		fightwin.draw(move1);

		fightwin.draw(move2);

		fightwin.draw(move3);

		fightwin.draw(move4);

		fightwin.draw(oppname);

		fightwin.draw(uname);


		if ((t1 != 0) && (elapsed.asMilliseconds() - t1 >3300))		//If 3.5 seconds has been over since attack was chosen
		{
			if (opp.hp <= 0)
			{
				fightwin.close();
				p.incatt();
				p.incdef();
				p.incspd(7);
				result(p, opp, 1);
			}
			else if (p.hp <= 0)
			{
				toxic = 0;
				fightwin.close();
				result(p, opp, 0);
			}

			t1 = 0;
			//Changing the turn for attacking
			if (turn == 4)
			{
				att = 3;
				turn = 0;	//PC's turn
				num = 0;
				oppturn = 0;
			}
			else
			{
				turn = 1;	//User's turn
				att = 3;
			}
			clock.restart();
		}
		//cout << "---" << elapsed.asMilliseconds()<<"****"<<t1 << "---\n";

		fightwin.display(); 
	}
}

void attackfunc(pokemon& attacker, pokemon& opponent, int move)//int move- Index No of attack used in class def of attacker         int num: 1-user is attacker   2-comp is attacker
{
	int hplost=0;
	int d = opponent.getdef(), a=attacker.getatt();
	int p = attacker.a[move].attpow;
	int style = attacker.a[move].style;
	
	//If toxic was used
	if (toxic == 1)	
		if (opponent.opp==0)	//If pokemon is user
		{
			if (opponent.hp > 50)
				hplost = opponent.hp*0.2;	//Opponent's HP decreases 20%
			else
				hplost = 12;
			opponent.hp -= hplost;
		}
	
	//If fake out was used
	if (attacker.opp==1)	//If attacker is opponent
		switch (miss)	//checking fake out
		{
		case 1:
			style = 10;	//Nothing happens due to attack
			miss = 2;
			break;
		case 2:
			style = 10;	//Nothing happens due to attack
			miss = 0;
			break;
		}


	int t;	//variable

	switch (style)
	{
		case 0:			//HP is lowered
			hplost = int(((p + pow(a, p / 100)) / d)*18.44);
			break;
		case 1:
			hplost = 0;
			if (opponent.getdef()>17)
				opponent.lowerdef(4);	//Defense is lowered by 5
			else if(opponent.getdef()>10)
				opponent.lowerdef(2);
			else
				opponent.lowerdef(1);
			break;

		case 2:
			t = 0.2*opponent.hp;
			attacker.hp += t+10;	//User's HP increases by 20%+10
			//cout << "****++++++****" << t << "\n";
			if (attacker.hp > 100)
				attacker.hp = 100;
			hplost = 0.2*opponent.hp;		//Opponent's HP decreases 20%
			break;

		case 3:
			hplost = 0;
			if (opponent.getatt()>17)
				opponent.loweratt(4);	//Attack is lowered by 5
			else if (opponent.getatt()>10)
				opponent.loweratt(2);
			else
				opponent.loweratt(1);
			break;

		case 4:
			hplost = 0;
			miss = 1;	//Opponent's next 2 attacks miss
			break;

		case 5:
			if (opponent.hp > 50)
				hplost = 0.4*opponent.hp;	//Opponent's HP decreases 40%
			else
				hplost = 15;
			break;

		case 6:
			hplost = int(((p + pow(a, p / 100)) / d)*18.44);	//HP is lowered
			if (opponent.getspd()>15)
				opponent.lowerspd();
			break;

		case 7:
			if (opponent.hp > 50)
				hplost = opponent.hp*0.2;		//Opponent's HP decreases 20%
			else
				hplost = 12;
			toxic = 1;
			break;

		case 10:		//Nothing happens
			hplost = 0;
			break;
	}

	if (style!=10)
		attacker.incspd(2);
	cout << "\n----" << opponent.hp << "   " << "++++++" << attacker.hp;
	opponent.hp -= hplost;
	cout << "\n----" << opponent.hp << "   " << "++++++" << attacker.hp << "\n";
	if (opponent.hp < 0)
		opponent.hp = 0;	
}

void result(pokemon& p, pokemon& opp, int winner)	//winner:  0-opponent won	1-user won
{
	RenderWindow window(VideoMode(1537, 827), "Result",Style::None);
	window.setPosition(sf::Vector2i(0, 0));

	char w[10], ch[25];
	if (winner == 1)
	{
		p.incspd(6);
		strcpy_s(w, "You Won!");
		if (characterchoice == 1)
			strcpy_s(ch, "pics\\D win.png");
		else if (characterchoice == 2)
			strcpy_s(ch, "pics\\L win.png");
	}
	else if (winner == 0)
	{
		p.decspd(3);
		strcpy_s(w, "You Lost!");
		if (characterchoice == 1)
			strcpy_s(ch, "pics\\D lose.png");
		else if (characterchoice == 2)
			strcpy_s(ch, "pics\\L lose.png");
	}

	//Background image
	RectangleShape background;
	background.setSize(sf::Vector2f(1537, 827));
	sf::Texture bckgd;
	if (bckgd.loadFromFile("pics\\result bkgd.png") == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	bckgd.setSmooth(true);
	background.setTexture(&bckgd);		//Texture
	
	//Character image
	RectangleShape character(sf::Vector2f(780, 830));
	sf::Texture image;
	if (image.loadFromFile(ch) == -1)
	{
		std::cout << "FAILED!!!" << "\n";
	}
	image.setSmooth(true);
	character.setTexture(&image);		//Texture
	character.setPosition(750, 5);

	Font font1;
	font1.loadFromFile("Fonts\\mvboli.ttf");

	//Result text
	Text r(w, font1, 150);	//size in pixels
	r.setStyle(Text::Bold);
	r.setColor(sf::Color::Blue);
	r.setPosition(100, 440);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					window.close();
					break;

				case sf::Keyboard::Escape:
					window.close();
					esc=1;
					break;
				}
			}
		}

		window.draw(background);

		window.draw(character);

		window.draw(r);

		window.display();
	}
}

/*
void exitgame()
{

	RenderWindow exitwin(VideoMode(1537, 827), "Esc Menu",Style::None);
	exitwin.setPosition(sf::Vector2i(0, 0));	// change the position of the window (relatively to the desktop)

	//exitwin.setMouseCursorVisible(false);		//hide mouse pointer in the game window

	//Button for Resume
	RectangleShape but1;
	but1.setSize(sf::Vector2f(270, 78));	//original size-(151,78)
	but1.setFillColor(sf::Color::Green);
	but1.setOutlineThickness(3);
	but1.setOutlineColor(sf::Color::Red);

	//Button for Main Menu
	RectangleShape but2;
	but2.setSize(sf::Vector2f(380, 76));
	but2.setFillColor(sf::Color::Green);
	but2.setOutlineThickness(3);
	but2.setOutlineColor(sf::Color::Red);

	//Button for Exit
	RectangleShape but3;
	but3.setSize(sf::Vector2f(130, 70));
	but3.setFillColor(sf::Color::Green);
	but3.setOutlineThickness(3);
	but3.setOutlineColor(sf::Color::Red);


	Font font1;
	font1.loadFromFile("Fonts\\BRLNSR.TTF");

	//"Resume" text
	Text resume;
	resume.setFont(font1);
	resume.setString("Resume");
	resume.setCharacterSize(80); // in pixels, not points!
	resume.setColor(sf::Color::Black);

	//"Main Menu" text
	Text mainme("Main Menu", font1, 80);
	mainme.setColor(sf::Color::Black);

	//"Exit" text
	Text exi("Exit", font1, 80);
	exi.setColor(sf::Color::Black);


	while (exitwin.isOpen())
	{
		int x = Mouse::getPosition().x;
		int y = Mouse::getPosition().y;
		
		Event event;
		while (exitwin.pollEvent(event))
		{
			exitwin.setActive(true);
			switch (event.type)
			{
			case sf::Event::Closed:
				exitwin.close();
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					if (x > 630 && x < 980 && y>247 && y < 329)		//If resume
					{
						exitwin.close();
						switch (esc)
						{
						case 1: 
							//title();
							esc = 0;
							break;

						case 2:
							disp(1);
							break;

						case 3:
							disp(2);
							break;

						case 4:
							choosech();
							break;

						case 5:
							choosepoke();
							break;

						case 7:
							fight(user, Duskull);
							break;
						}
					}
					else if (x > 572 && x < 956 && y>384 && y < 463)	//If main menu
					{
						title();
					}
					else if (x > 697 && x < 832 && y>517 && y < 593)	//If exit
					{
						exit(0);
					}
					break;
				}
				break;

			//case sf::Event::KeyPressed:
			//	switch (event.key.code)
			//	{
			//	case sf::Keyboard::Return:
			//		exitwin.close();
			//		break;

			//	case sf::Keyboard::Escape:
			//		exit(0);
			//		break;
			//	}
			}
		}



		but1.setPosition(634, 250);
		exitwin.draw(but1);	//resume button

		resume.setPosition(637, 233);
		exitwin.draw(resume);	//Resume text

		but2.setPosition(575, 386);
		exitwin.draw(but2);	//main menu button

		mainme.setPosition(578, 370);
		exitwin.draw(mainme);	//Main Menu text

		but3.setPosition(700, 520);
		exitwin.draw(but3);	//exit button

		exi.setPosition(703, 502);
		exitwin.draw(exi);	//Exit text


		exitwin.display();
	}

}*/