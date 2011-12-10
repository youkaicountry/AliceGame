//This is the file housing main.
//In this source, I left in all the commented code I used
//for testing purposes, so don't mind those.



#include "player.h"
#include "bullet.h"
#include <iostream.h>
#include "gamespace.h"
#include <irrlicht.h>
#include "spritenote.h"
#include <windows.h>
#include "keystate.h"
#include "irrevent.h"
#include "timesensor.h"
#include <sstream>
#include <fstream.h>
#include "aiplayer.h"
#include <wchar.h>
#include "random.h"
#include "dna.h"
#include <vector>
#include "generation.h"

using namespace std;
using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

//SET UP VARIABLES
//enum {LOC_MAINMENU = 1, LOC_SCORELIST = 2, LOC_GAME = 3, LOC_BAILING = 4};
enum {LOC_MAINMENU, LOC_SCORELIST, LOC_GAME, LOC_BAILING};
int pllocation;
vector<core::rect<s32> > spritelist; //list of t3h sprites.
vector<SpriteNote>* pspritenotevector;
vector<SpriteNote> spritenotevector;
//u32 FPS, delay;
KeyState theKeyState;
KeyState oldKeyState;
CIrrLichtEvent irrevent;
AIPlayer theAI;
Random ran;
bool human;
DNA aidna;
vector<int> replay;
bool replaysave;
bool watchingreplay;
char replayfileout[100];
char replayfilein[100];
char tem[20];
int replayloc;

//AN OLD FUNCTION USED FOR TIMING. NOT ACTUALLY USED ANYMORE
u32 calcDelay(u32 fps)
{
    return 1000/fps;
}

//USED FOR REPLAY SAVING
void putInt(ostream *out, int x)
{
   out->put( x        & 0xFF);
   out->put((x >>  8) & 0xFF);
   out->put((x >> 16) & 0xFF);
   out->put((x >> 24) & 0xFF);
}

int main()
{   
   //testing mutation a bit
   //for (int aid = 0;aid < 5;aid++)
   //{
   //  aidna.mutate(.05,1);
   //}
   
   //aidna.save("stock.dna");
   //aidna.clear();
   //aidna.load("test.dna");
   
   //aidna.save("empty.dna");
   
   //THIS LOADS THE DEFAULT HAND MADE AI
   aidna.load("stock.dna");
   
   //for (int jj = 0;jj < 10;jj++)
   //{
    //  printf("%d\n",(rand()%5)+0);
   //}
   
   
   //Random rando;
   //printf("%d", rando.nextInt(2));
   
   
    //printf("test %d",(int)false);
    
    //HERE IS THE QUICKLY PROGRAMMED MENU SYSTEM. i THINK THIS
    //CODE IS FAIRLY SELF EXPLANATORY
    cout << "1. Play!\n2. Have Stock AI Play\n3. Have AI From a File Play\n4. Genetically produce AI\n5. Watch Replay\n6. Examine DNA file\n?: ";
    int a = 1;
    cin >> a;
    if (a == 1) 
    {
       human = true;
       printf("\n\nSave Replay?\n");
       
       cin >> tem;
       if ((strcmp(tem, "y") == 0) || (strcmp(tem, "Y") == 0) || (strcmp(tem, "yes") == 0) || (strcmp(tem, "YES") == 0)) // Equal strings || tem == "Y" || tem == "yes" || tem == "YES")
       {
          printf("\n\nReplay File Name? (without extension)\n?: ");
          cin >> replayfileout; strcat(replayfileout, ".rep");
          replaysave = true;
          watchingreplay = false;
       } 
    }
    if (a == 2)
    {
       human = false;
       printf("\n\nSave Replay?\n");
       
       cin >> tem;
       if ((strcmp(tem, "y") == 0) || (strcmp(tem, "Y") == 0) || (strcmp(tem, "yes") == 0) || (strcmp(tem, "YES") == 0)) // Equal strings || tem == "Y" || tem == "yes" || tem == "YES")
       {
          printf("\n\nReplay File Name? (without extension)\n?: ");
          cin >> replayfileout; strcat(replayfileout, ".rep");
          replaysave = true;
          watchingreplay = false;
       } 
    }
    
    if (a == 3)
    {
       printf("\n\nDNA File Name? (without extension)\n?: ");
       cin >> replayfileout; strcat(replayfileout, ".dna");  
       aidna.load(replayfileout);
       human = false;
       printf("\n\nSave Replay?\n");
       
       cin >> tem;
       if ((strcmp(tem, "y") == 0) || (strcmp(tem, "Y") == 0) || (strcmp(tem, "yes") == 0) || (strcmp(tem, "YES") == 0)) // Equal strings || tem == "Y" || tem == "yes" || tem == "YES")
       {
          printf("\n\nReplay File Name? (without extension)\n?: ");
          cin >> replayfileout; strcat(replayfileout, ".rep");
          replaysave = true;
          watchingreplay = false;
       } 
    }
    
    if (a == 4)
    {
         //this is where genetic production code goeth
	      //GameSpace gs(1, 0, 800, 0, 600, ran.nextInt(1000000));
	      //while (gs.updateGameState(theKeyState) == 1)
	      //{
         //   theKeyState = theAI.update(&gs, &gs.thePlayer, aidna, theKeyState);
         //}
         //printf("Score: %d\n", gs.thePlayer.getScore());
         //printf("Lives: %d\n", gs.thePlayer.getLives());
         SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
         
         printf("\n\nStarting DNA File Name? (without extension) (stock is a good start point)\n?: ");
          cin >> replayfileout; strcat(replayfileout, ".dna");
         
         printf("\n\nReaction Time Lock Value (-1 for no lock)?\n?: ");
         int rlock;
         cin >> rlock;
         
         printf("\n\nSimulation Seed?\n?: ");
         int tseed;
         cin >> tseed;
         Generation ge(replayfileout, tseed, rlock);
         
         printf("\n\nSave Best DNA As? (without extension)\n?: ");
         cin >> replayfileout; strcat(replayfileout, ".dna");
         
         printf("\n\nNumber Of Generations?\n?: ");
         int runlength;
         cin >> runlength;
         
         printf("\n\nCrossover Chance (.1 is reasonable)\n?: ");
         double crosschance;
         cin >> crosschance;
         
         printf("\n\nMutation Chance (.05 is reasonable)\n?: ");
         double mutchance;
         cin >> mutchance;
         
         printf("\n\nMutation Severity (5-15 is reasonable)\n?: ");
         double mutsev;
         cin >> mutsev;
         
         printf("\n\nTournament Size (5 is reasonable)\n?: ");
         int tsize;
         cin >> tsize;
         
         printf("Simulating\n");
         for (int loop = 0;loop < runlength; loop++)
         {
            ge = ge.formNextGeneration(crosschance, mutchance, mutsev, tsize, loop);
            
         }
         ge.simulateAll(); //extra simulate all so you can see
         SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
         ge.saveBest(replayfileout);
         printf("All Done. Best Fitness = %d\n", ge.bestFitness());
         system("pause");
         return 1;
    }
	      
    
    if (a == 5)
    {
         watchingreplay = true;
         replaysave = false;
         human = false;
         printf("\n\nReplay File Name? (without extension)\n?: ");
         cin >> replayfilein; strcat(replayfilein, ".rep");
         ifstream myFile(replayfilein, ios::in | ios::binary);
         while(myFile.eof() == false)
         {
            int v;
            myFile.read((char*) (&v), sizeof(int));
            replay.push_back(v);
         }
         myFile.close();
         //ifstream myFile ("data.bin", ios::in | ios::binary);
    }
    if (a == 6)
    {
         replayfilein;
         printf("\n\nDNA File Name? (without extension)\n?: ");
         cin >> replayfilein; strcat(replayfilein, ".dna");
         aidna.load(replayfilein);
         printf("\n\n");
         printf("PanicRadius: %g, Reaction: %d, CareZone: %g, GameLine: %g\n", aidna.bulletpanic, aidna.reactioncycles, aidna.carefulzone, aidna.gameline);
         printf("                                    POWERUP ST. BULLETS ST. PANIC ST. \n");
         printf("BULLETSEE                           %g           %g           %g\n",aidna.bulletsee[0],aidna.bulletsee[1],aidna.bulletsee[2]);
         printf("E BULLET ATTRACTION                 %g           %g           %g\n",aidna.ebulletattract[0],aidna.ebulletattract[1],aidna.ebulletattract[2]);
         printf("E BULLET ATT. INV. PROP. EXPONENT   %g           %g           %g\n",aidna.ebulletattractpower[0],aidna.ebulletattractpower[1],aidna.ebulletattractpower[2]);
         printf("E BULLET REPULSION                  %g           %g           %g\n",aidna.ebulletrepel[0],aidna.ebulletrepel[1],aidna.ebulletrepel[2]);
         printf("E BULLET REP. INV. PROP. EXPONENT   %g           %g           %g\n",aidna.ebulletrepelpower[0],aidna.ebulletrepelpower[1],aidna.ebulletrepelpower[2]);
         printf("\n");
         printf("E LINE ATTRACTION                   %g           %g           %g\n",aidna.elineattract[0],aidna.elineattract[1],aidna.elineattract[2]);
         printf("E LINE ATT. INV. PROP. EXPONENT     %g           %g           %g\n",aidna.elineattractpower[0],aidna.elineattractpower[1],aidna.elineattractpower[2]);
         printf("E LINE REPULSION                    %g           %g           %g\n",aidna.elinerepel[0],aidna.elinerepel[1],aidna.elinerepel[2]);
         printf("E LINE REP. INV. PROP. EXPONENT     %g           %g           %g\n",aidna.elinerepelpower[0],aidna.elinerepelpower[1],aidna.elinerepelpower[2]);
         printf("\n");
         printf("W LINE ATTRACTION                   %g           %g           %g\n",aidna.wlineattract[0],aidna.wlineattract[1],aidna.wlineattract[2]);
         printf("W LINE ATT. INV. PROP. EXPONENT     %g           %g           %g\n",aidna.wlineattractpower[0],aidna.wlineattractpower[1],aidna.wlineattractpower[2]);
         printf("W LINE REPULSION                    %g           %g           %g\n",aidna.wlinerepel[0],aidna.wlinerepel[1],aidna.wlinerepel[2]);
         printf("W LINE REP. INV. PROP. EXPONENT     %g           %g           %g\n",aidna.wlinerepelpower[0],aidna.wlinerepelpower[1],aidna.wlinerepelpower[2]);
         printf("\n");
         printf("POWERUP ATTRACTION                  %g           %g           %g\n",aidna.powerupattract[0],aidna.powerupattract[1],aidna.powerupattract[2]);
         printf("POWERUP ATT. INV. PROP. EXPONENT    %g           %g           %g\n",aidna.powerupattractpower[0],aidna.powerupattractpower[1],aidna.powerupattractpower[2]);
         printf("POWERUP REPULSION                   %g           %g           %g\n",aidna.poweruprepel[0],aidna.poweruprepel[1],aidna.poweruprepel[2]);
         printf("POWERUP REP. INV. PROP. EXPONENT    %g           %g           %g\n",aidna.poweruprepelpower[0],aidna.poweruprepelpower[1],aidna.poweruprepelpower[2]);
         printf("\n");
         system("pause");
         return 0;
    }
         
    //SET UP SENSORS
    //for(int x=0; x< sizeof(irr::EKEY_CODE); x++) keys[x] = false;
    TimeSensor* graphicsensor = TimeSensor::getNewClockSensor();
    TimeSensor* inputsensor = TimeSensor::getNewClockSensor();
    TimeSensor* gamesensor = TimeSensor::getNewClockSensor();
    
    //SET UP GRAPHICS GARBAGE
    //(IRRLICHT USED FOR GRAPHICS)
    irrevent.Init();
    pllocation = LOC_GAME;
    video::E_DRIVER_TYPE driverType;
    //driverType = video::EDT_SOFTWARE2;
    driverType = video::EDT_OPENGL;
    IrrlichtDevice *device = createDevice(driverType,
		core::dimension2d<s32>(800, 600), 16,
			false/*fullscreen*/, false/*stencilbuffer*/, true/*vsync*/, 0);
	 device->setWindowCaption(L"Shooter");
	 video::IVideoDriver* driver = device->getVideoDriver();
	 device->getFileSystem()->addZipFileArchive("./data.zip");
	 video::ITexture* images = driver->getTexture("./sprites.png");
	 driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
    gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    gui::IGUIStaticText* scoretext = guienv->addStaticText(L"",
	        core::rect<int>(10,10,200,22), true);
	 gui::IGUIStaticText* livestext = guienv->addStaticText(L"",
	        core::rect<int>(10,30,200,42), true);
    device->getCursorControl()->setVisible(false);
    
    //THIS LOOP HERE LOADS THE SPRITES FROM THE SPRITE TABLE FILE
    //FPS = 100; delay = calcDelay(FPS);
    for (int y = 0;y<5;y++)
    {
        for (int x = 0;x<12;x++)
        {
            int ax = 1+(x*39)+(x*2);
            int ay = 1+(y*39)+(y*2);
            int bx = ax+39;
            int by = ay+39;
            spritelist.push_back(core::rect<s32>(ax,ay,bx,by)); 
        }
    }
    /*spritelist.push_back(core::rect<s32>(1,1,39,39));  //BULLET(0)
    spritelist.push_back(core::rect<s32>(42,1,80,39)); //PLAYER(1)
    spritelist.push_back(core::rect<s32>(83, 1, 121, 39)); //PBULLET(2)
    spritelist.push_back(core::rect<s32>(124, 1, 162, 39)); //PBULLET(3)
    spritelist.push_back(core::rect<s32>(165, 1, 203, 39)); //PBULLET(4)
    spritelist.push_back(core::rect<s32>(206, 1, 244, 39)); //EBULLET(5)
    spritelist.push_back(core::rect<s32>(247, 1, 285, 39)); //EBULLET(6)
    spritelist.push_back(core::rect<s32>(288, 1, 326, 39)); //EBULLET(7)
    spritelist.push_back(core::rect<s32>(329, 1, 367, 39)); //ENEMY(8)
    spritelist.push_back(core::rect<s32>(370, 1, 408, 39)); //PLAYERINV(9)
    spritelist.push_back(core::rect<s32>(411, 1, 449, 39)); //PARTICLE(10)
    spritelist.push_back(core::rect<s32>(452, 1, 488, 39)); //PARTICLE(11)
    //where in the sprite map
	//core::rect<s32> imp2(387,15,423,78);*/
	
	pspritenotevector = &spritenotevector;
	
	//SET UP REPLAY SAVING STUFF IF APPLICABLE
	int sa = ran.nextInt(1000000);
	if (replaysave) {replay.push_back(sa);}
	if (watchingreplay) {sa = replay[0];}
	GameSpace gs(1, 0, 800, 0, 600, sa, false);
	replayloc = 1;
	device->setEventReceiver(&irrevent);
	
	//SET UP THE TIMER FRAME RATES AND LAMBDAS
	//graphicsensor->setLambda(.20);graphicsensor->setFrequency(60);
	//graphicsensor->reset();
    inputsensor->setLambda(.07);inputsensor->setFrequency(55);
	inputsensor->reset();
    gamesensor->setLambda(.07);gamesensor->setFrequency(80);
	gamesensor->reset();
	
	//THE MAIN GAME LOOP
    while(device->run() && driver && pllocation != LOC_BAILING)
    {
        if (device->isWindowActive())
		{
            //u32 timeopen = device->getTimer()->getTime();
            //cout << timeopen<<"     ";
            //Sleep(1);
            
           if (pllocation == LOC_MAINMENU)
           {
                driver->beginScene(true, true, video::SColor(0,120,102,136));
				driver->endScene();
           }
           
           else if (pllocation == LOC_GAME)
           {
                //GATHER KEYS or AI KEYS IF AI IS ON!!! THIS IS WHERE AI
                //SHOULD BE CALLED
                 //if(keys[irr::KEY_DOWN]) cout << "DOWN"; 
                
                //if (inputsensor->poll())
                if (gamesensor->poll())
                {
                   //cout << "input";
                   //gamesensor->wait();
                   
                   
                   //THIS GRABS THE KEY STATES FROM THE KEYBOARD IF A HUMAN IS PLAYING
                   if (human == true)
                   {
                      theKeyState.clearKeys();
                      if (irrevent.IsKeyDown(KEY_UP)) {theKeyState.setUp(true);} 
                      if (irrevent.IsKeyDown(KEY_DOWN)) {theKeyState.setDown(true);}
                      if (irrevent.IsKeyDown(KEY_LEFT)) {theKeyState.setLeft(true);}
                      if (irrevent.IsKeyDown(KEY_RIGHT)) {theKeyState.setRight(true);}
                      if (irrevent.IsKeyDown(KEY_KEY_Z)) {theKeyState.setZ(true);}
                      if (irrevent.IsKeyDown(KEY_KEY_X)) {theKeyState.setX(true);}
                      if (irrevent.IsKeyDown(KEY_ESCAPE)) {theKeyState.setEsc(true);}
                      if (irrevent.IsKeyDown(KEY_SHIFT)) {theKeyState.setShift(true);}
                    }
                    else
                    {
                        //THIS HANDLES REPLAYS
                        if (watchingreplay == true)
                        {
                           while(gs.cycle == replay[replayloc])
                           {
                              if (replay[replayloc + 1] == 0)
                              {
                                 theKeyState.setUp((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 1)
                              {
                                 theKeyState.setDown((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 2)
                              {
                                 theKeyState.setLeft((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 3)
                              {
                                 theKeyState.setRight((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 4)
                              {
                                 theKeyState.setZ((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 5)
                              {
                                 theKeyState.setX((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 6)
                              {
                                 theKeyState.setEsc((bool)replay[replayloc + 2]);
                              }
                              if (replay[replayloc + 1] == 7)
                              {
                                 theKeyState.setShift((bool)replay[replayloc + 2]);
                              }
                              replayloc += 3;
                           }
                        }
                        else
                        {
                           //THIS IS IF AN AI PLAYER IS PLAYING
                           //theKeyState.clearKeys();
                           theKeyState = theAI.update(&gs, &gs.thePlayer, aidna, theKeyState);
                        }
                    }
                    //THIS CHECKS IF THE USER HAS PRESSED ESCAPE
                    if (irrevent.IsKeyDown(KEY_ESCAPE)) {theKeyState.setEsc(true);}
                
                
                
                
                //UPDATE GAME
                //if (gamesensor->poll())
                //{
                    //cout << "game";
                    
                   //IF A REPLAY IS BEING SAVED, THIS CHECKS IF ANY KEY STATES
                   //HAVE CHANGED SINCE LAST CYCLE. IF SO, RECORD THE 
                   //DIFFERENCE.
                   if (replaysave)
                   {
                        if (theKeyState.isUp() != oldKeyState.isUp())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(0);
                           replay.push_back((int)theKeyState.isUp());
                        }
                        if (theKeyState.isDown() != oldKeyState.isDown())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(1);
                           replay.push_back((int)theKeyState.isDown());
                        }
                        if (theKeyState.isLeft() != oldKeyState.isLeft())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(2);
                           replay.push_back((int)theKeyState.isLeft());
                        }
                        if (theKeyState.isRight() != oldKeyState.isRight())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(3);
                           replay.push_back((int)theKeyState.isRight());
                        }
                        if (theKeyState.isZ() != oldKeyState.isZ())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(4);
                           replay.push_back((int)theKeyState.isZ());
                        }
                        if (theKeyState.isX() != oldKeyState.isX())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(5);
                           replay.push_back((int)theKeyState.isX());
                        }
                        if (theKeyState.isEsc() != oldKeyState.isEsc())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(6);
                           replay.push_back((int)theKeyState.isEsc());
                        }
                        if (theKeyState.isShift() != oldKeyState.isShift())
                        {
                           replay.push_back(gs.cycle);
                           replay.push_back(7);
                           replay.push_back((int)theKeyState.isShift());
                        }
                        oldKeyState = theKeyState;
                   }
                   
                   //THIS IS THE CALL TO THE GAME OBJECT
                   if (gs.updateGameState(theKeyState) !=1 ) {theKeyState.setEsc(true);}
                
                } 
                //BEGIN GRAPHICS HANDLING
                //THIS SECTION OF CODE DOES ALL OF THE CALLS TO
                //IRRLICHT, AND SETS THE SPRITES
                
                    //cout << "graphic";
                   driver->beginScene(true, true, video::SColor(0,0,0,0));
                   
                   //HERE, THE PARALLAXING STARS ARE DRAWN
                   list<Star>::iterator s;
                   for(s=gs.lStars.begin(); s != gs.lStars.end();)
                   {
                      if (s->getY() > gs.screenbottom)
                      {
                         s = gs.lStars.erase(s);
                         
                         gs.lStars.push_front(Star(ran.nextDouble(800),0,ran.nextDouble(100)));
                      }
                      else
                      {
                        
                         s->update(1.8);
                         int co = (int)(((1 - (s->getZ()/100))*170) + 74);
                         driver->draw2DRectangle(video::SColor(co,co,co,co),
                                                 core::rect<int>((int)(s->getX()),(int)(s->getY()),(int)(s->getX()+1),(int)(s->getY()+1)),
                                                 NULL);
                         s++;
                      }  
                      //vsn->push_back(SpriteNote((int)j->getX(), (int)j->getY(), j->getSprite()));
                   }
                   
                   //THIS CYCLES THROUGH THE MAIN
                   gs.getSprites(pspritenotevector, theKeyState);
                   int j;
                   for (j = 0; j < pspritenotevector->size();j++)
                   {
                      driver->draw2DImage(images, core::position2d<s32>(spritenotevector[j].getX()-20,spritenotevector[j].getY()-20),
				              spritelist[spritenotevector[j].getSprite()], 0, video::SColor(255,255,255,255), true); 
                   }
                   
                   driver->draw2DRectangle(video::SColor(255,255,255,255),
                                                 core::rect<int>(10,10,200,22),
                                                 NULL);
                                                 
                  driver->draw2DRectangle(video::SColor(255,255,255,255),
                                                 core::rect<int>(10,30,200,42),
                                                 NULL);
                   
                   
                   //TEXT DISPLAYS
                   wchar_t buf[80];
                   swprintf(buf,80,L"Score: %d",gs.thePlayer.getScore());
                   scoretext->setText(buf);
                   
                   swprintf(buf,80,L"Lives: %d",gs.thePlayer.getLives());
                   livestext->setText(buf);
                   //guienv->addStaticText(L"Hello World! This is the Irrlicht Software engine!",
	               //core::rect<int>(10,10,200,22), true);
                   
                   
                  // stringstream ss;
                  // string str;
                  // ss << 31337;
                  // ss >> str;
                  // font->draw(L""+str, 
			   	//core::rect<s32>(10,10,10,10),
				//video::SColor(255,255,255,255));
                   guienv->drawAll();
                   driver->endScene();
                //END GRAPHICS HANDLING
                
           }
        //Sleep(5);
        //u32 timeend = device->getTimer()->getTime();
        //u32 timespent = timeend - timeopen;
        //u32 delayleft = delay - timespent; 
        //if (delayleft > 0) {Sleep(delayleft);}
           if (theKeyState.isEsc()) {break;}
        }
       if (theKeyState.isEsc()) {break;}
       Sleep(10);  
    
   }
if (replaysave)
{
   //ofstream myFile;
   //(replayfileout, ios::out | ios::binary);
   fstream myFile(replayfileout, ios::out | ios::binary);
   //for (int ii = 0;ii < replay.size();ii++)
   // {
   //   myFile << replay[ii];
   //}
   
for (int ii = 0;ii < replay.size();ii++)
   putInt(&myFile, replay[ii]);
   
   
   myFile.close();
}

}

