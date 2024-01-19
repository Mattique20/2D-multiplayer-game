#include<iostream>
#include <cstdlib>
#include <ctime>
#include<pthread.h>
#include<signal.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;
int rscore=-2;
int mscore=0;
bool win;

struct threadarg
{
    sf::Sprite *s1;
    sf::Vector2f *m1;
};

int NxN()
{
    srand(time(NULL));
    int randomNum = rand() % 90 + 10;
    randomNum*=1;
    int num= 410/randomNum;
    num= num%25;
    if(num <= 10)
    {
        num+=15;
    }
    return num;
}

void *moveronaldo(void* arg) 
{
   threadarg* p1=(threadarg*)arg;
    while(true) 
    {
        if (p1->m1->x != 0.f || p1->m1->y != 0.f ) 
        {
           p1->s1->move(*(p1->m1)) ;      
        }
        if (p1->m1->x== 0.f || p1->m1->y == 0.f)
        {
            cout << "Player 1 is moving\n";
        }
        if(rscore==10 || mscore==10 || win==true)
        {
            break;       
        }
        usleep(10000); // delay for 10ms
    }
    pthread_exit(0);

}

void *moveMessi(void* arg) 
{
    threadarg* p1=(threadarg*)arg;
    while(true) 
    {
        if (p1->m1->x != 0.f || p1->m1->y != 0.f) {
            p1->s1->move(*(p1->m1));
        }
        if (p1->m1->x != 0.f || p1->m1->y != 0.f)
        {
            cout << "Player 2 is moving\n";
        }
         if(rscore==10 || mscore==10 || win==true)
        {
            break;       
        }
        usleep(10000); // delay for 10ms
    }
    pthread_exit(0);
}

int main()
{    
    win=false;
    int trophy_no=0;
    int num= NxN();

    cout << num << endl;
    int gridsize= 585/num;
    
    float xcord[num];
    float ycord[num];
    //-------------------------------------------_____GRID_WHITE_SQUARE________-------------------------------------------------//
    sf::RectangleShape rectangle(sf::Vector2f(gridsize  , gridsize));


    sf::RenderWindow window(sf::VideoMode(600, 600), "OS A2");

    //-------------------------------------------RONALDO-----------------------------------------------//
    sf::Texture texture;
    if (!texture.loadFromFile("r.png"))
    {
        // Error handling
        return EXIT_FAILURE;
    }      
    sf::Sprite sprite(texture);
    sprite.setTexture(texture);
    sf::Vector2f scale = rectangle.getScale();
    sprite.setScale(2*(gridsize/sprite.getLocalBounds().width) ,2*(gridsize/sprite.getLocalBounds().height));
   
   
    //-------------------------------------------MESSI-----------------------------------------------------------------//
    sf::Texture texture2;
    if (!texture2.loadFromFile("m.png"))
    {
        // Error handling
        return EXIT_FAILURE;
    }      
    sf::Sprite sprite2(texture2);
    sprite2.setTexture(texture2);
    sf::Vector2f scale2 = rectangle.getScale();
    sprite2.setScale(2*(gridsize/sprite2.getLocalBounds().width) ,2*(gridsize/sprite2.getLocalBounds().height));
    sprite2.setPosition(555,0);
    //-----------------------------------------------trophy---------------------------------------------------------//
    
    float object_x = 300.f;
    float object_y = 300.f;
    sf::Texture t1;
    if (!t1.loadFromFile("b.png"))
    {
        // Error handling
        return EXIT_FAILURE;
    }      
    sf::Sprite spirte3(t1);
    spirte3.setTexture(t1);
    sf::Vector2f scale3 = rectangle.getScale();
    spirte3.setScale(2*(gridsize/spirte3.getLocalBounds().width) ,2*(gridsize/spirte3.getLocalBounds().height));


    float object2_x = 300.f;
    float object2_y = 300.f;
    sf::Texture t2;
    if (!t2.loadFromFile("b.png"))
    {
        // Error handling
        return EXIT_FAILURE;
    }      
    sf::Sprite sprite4(t2);
    sprite4.setTexture(t2);
    sf::Vector2f scale4 = rectangle.getScale();
    sprite4.setScale(2*(gridsize/sprite4.getLocalBounds().width) ,2*(gridsize/sprite4.getLocalBounds().height));
    //------------------------------------------R_MOVEMENT-----------------------------------------------------------//
    sf::Vector2f movement(0.f, 0.f);
    sf::Vector2f movement2(0.f, 0.f);
    float speed = 3.f;
    float speed2 = 3.f;
    
    //-------------------------------------------SUIIIII-----------------------------------------------------------//
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("s.wav"))
    return EXIT_FAILURE;
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("c.wav"))
    return EXIT_FAILURE;
    sf::Sound sound2;
    sound2.setBuffer(buffer2);



    //_____________________________________PTHREADSS_________________________________________//
        // Create threads for player movement
         threadarg p1;
         p1.s1=&sprite;
         p1.m1=&movement;
         pthread_t player1Thread;
         pthread_create(&player1Thread, NULL, moveronaldo , &p1);
         pthread_t player2Thread;
         threadarg p2;
         p2.s1=&sprite2;
         p2.m1=&movement2;
         pthread_create(&player2Thread, NULL, moveMessi , &p2);
        
    //-----------------------------------------------window----------------------------------------------------//
    while (window.isOpen())
    {
        sf::Event event;
        
        //--------------------events-------------//
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
             {   
                window.close();
                win=true;
             }
               
               //------------------movement---------------//
               if (event.type == sf::Event::KeyPressed)
               {
                    if (event.key.code == sf::Keyboard::Up)
                        movement.y = -speed;
                    else if (event.key.code == sf::Keyboard::Down)
                        movement.y = speed;
                    else if (event.key.code == sf::Keyboard::Left)
                        movement.x = -speed;
                    else if (event.key.code == sf::Keyboard::Right)
                        movement.x = speed;                    


                    else if (event.key.code == sf::Keyboard::A) 
                         movement2.x = -speed2;
                    else if (event.key.code == sf::Keyboard::D)
                        movement2.x = speed2;
                    else if (event.key.code == sf::Keyboard::W) 
                        movement2.y = -speed2;
                    else if (event.key.code == sf::Keyboard::S)
                        movement2.y = speed2;
                }

                 if (event.type == sf::Event::KeyReleased)
                 {
                     if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                     movement.y = 0.f;
                     else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                     movement.x = 0.f;

                     if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
                     movement2.y = 0.f;
                     else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
                     movement2.x = 0.f;
                 }
        }    
        


        //grid
        window.clear();

        //_______________________________________GRID_______________________________//
         for(int h=0; h< num; h++)
        {                                        
            for(int v=0; v< num; v++)
            {   
                // if((h+v)%2==0)
                // {                              
                    rectangle.setFillColor(sf::Color::White);
                    rectangle.setPosition(h+(h*gridsize), v+(v*gridsize));
                    window.draw(rectangle);
              //  } 
            }
            
        }

        //---------------------------------------------movement boundriesss-----------------------------------------------------------//
        if((sprite.getPosition().x>=-5 && sprite.getPosition().x <=585) && (sprite.getPosition().y>=-5 && sprite.getPosition().y <=585))
        {
           sprite.move(movement);
        }
        else if(sprite.getPosition().x <0)
        {
            sprite.setPosition(0.f,sprite.getPosition().y);
        }
        else if(sprite.getPosition().x >=585)
        {
            sprite.setPosition(sprite.getPosition().x-10,sprite.getPosition().y);
        }
        else if(sprite.getPosition().y <0)
        {
            sprite.setPosition(sprite.getPosition().x,0.f);
        }
        else if(sprite.getPosition().y >570)
        {
            sprite.setPosition(sprite.getPosition().x-10,sprite.getPosition().y-20);
        }
        //____________________________________________________MESSI MOVEMENT________________________________________________________
       if((sprite2.getPosition().x>=-5 && sprite2.getPosition().x <=585) && (sprite2.getPosition().y>=-5 && sprite2.getPosition().y <=585))
        {
           sprite2.move(movement2);
        }
        else if(sprite2.getPosition().x <0)
        {
            sprite2.setPosition(0.f,sprite2.getPosition().y);
        }
        else if(sprite2.getPosition().x >=585)
        {
            sprite2.setPosition(sprite2.getPosition().x-10,sprite2.getPosition().y);
        }
        else if(sprite2.getPosition().y <0)
        {
            sprite2.setPosition(sprite2.getPosition().x,0.f);
        }
        else if(sprite2.getPosition().y >570)
        {
            sprite2.setPosition(sprite2.getPosition().x-10,sprite2.getPosition().y-20);
        }
        

        //sui sound
        if (movement.x != 0.f || movement.y != 0.f)
        sound.play();
        if (movement2.x != 0.f || movement2.y != 0.f) 
         {   sound2.play(); }   



        //--------------------------------score calculation-----------------------------------------
        
    if (sprite.getGlobalBounds().intersects(spirte3.getGlobalBounds()))
        {
            object_x = rand() % 500 + 50.f;
            object_y = rand() % 500 + 50.f;
            spirte3.setPosition(object_x, object_y);
            rscore++;
        }
        if (sprite.getGlobalBounds().intersects(sprite4.getGlobalBounds()))
        {
            object2_x = rand() % 500 + 50.f;
            object2_y = rand() % 500 + 50.f;
            sprite4.setPosition(object2_x, object2_y);
            rscore++;
        }
        if (sprite2.getGlobalBounds().intersects(spirte3.getGlobalBounds()))
        {
            object_x = rand() % 500 + 50.f;
            object_y = rand() % 500 + 50.f;
            spirte3.setPosition(object_x, object_y);
            mscore++;
        }
        if (sprite2.getGlobalBounds().intersects(sprite4.getGlobalBounds()))
        {
            object2_x = rand() % 500 + 50.f;
            object2_y = rand() % 500 + 50.f;
            sprite4.setPosition(object2_x, object2_y);
            mscore++;
        }

         if(rscore==10 || mscore==10)
        {
            break;       
        }
       
        

        window.draw(sprite);
        window.draw(sprite2);
        window.draw(spirte3);
        window.draw(sprite4);
        window.display();
    }
    
    pthread_join(player1Thread,NULL);
    pthread_join(player2Thread,NULL);
    
    cout<<"------------------------------------------------------\n";
    cout<<"------------------------------------------------------\n";
    cout<<"------------------------------------------------------\n";
    cout<<"-----------------------WINNER-------------------------\n";
    cout<<"------------------------------------------------------\n";
    cout<<"------------------------------------------------------\n";
    cout<<"------------------------------------------------------\n";

   cout <<"               RONALDO: " <<  rscore << endl;
   cout <<"               MESSI  : " << mscore << "\n\n";
        if(rscore>mscore)
        {
            cout << "-----------------RONALDO the G.O.A.T-----------------\n\n";
            sound.play();
        }
        else
        {
        cout << "-----------------MESSI the G.O.A.T-----------------\n\n";
        sound2.play();
        }
    
    return 0;

}