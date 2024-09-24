#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <iomanip>
#include <cassert>
#include <random>

using namespace std;


mt19937 rng(2288);

float get_dist(sf::Vector2f a, sf::Vector2f b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

class Ball
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;

    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius) : position(position), velocity(velocity), radius(radius)
    {
    }

    void update(float dt)
    {
        ///return;
        position += velocity * dt;
        float g = 1;
        if (position.x + radius / g > +1.5 || position.x - radius / g < -1) velocity.x *= -1;
        if (position.y + radius / g > +1.5 || position.y - radius / g < -1) velocity.y *= -1;
    }

};

float randoms[100];
sf::Vector2f ballposition[100];
float ballradius[100];

long double xc, yc, sz;


const float pi = 3.141592653589793;

float Gauss(sf::Vector2f point, sf::Vector2f origin, float sigma) 
{
    const float sq2pi = sqrt(2 * pi);
    ///float 
    point -= origin;
    float x = point.x, y = point.y;
    return 1 / (sigma * sq2pi) * exp(-(x * x + y * y) / (2 * sigma * sigma));
}

void run()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "Meat Ballz");
    sf::View view;
    view.setSize(sf::Vector2f(1.1, 1.1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);
    sf::CircleShape shp;
    shp.setRadius(0.1);
    shp.setOrigin(shp.getRadius() * sf::Vector2f(1, 1));
    shp.setPosition(sf::Vector2f(0.5, 0.5));
    sf::Clock frameClock;
    sf::Clock secClock;


    int p = 300;
    sf::VertexArray varray(sf::Quads, 4 * p * p);
    int y = 0;
    float eps = (float)1 / (float)p;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            varray[y++].position = sf::Vector2f(eps * i, eps * j);
            varray[y++].position = sf::Vector2f(eps * i, eps * (j + 1));
            varray[y++].position = sf::Vector2f(eps * (i + 1), eps * (j + 1));
            varray[y++].position = sf::Vector2f(eps * (i + 1), eps * j);
        }
    }

    uniform_real_distribution<float> distrib01;

    vector<Ball> balls;
    for (int i = 0; i < 10; i++)
    {
        sf::Vector2f position = sf::Vector2f(distrib01(rng), distrib01(rng));
        sf::Vector2f velocity = sf::Vector2f(distrib01(rng), distrib01(rng)) * 0.5f;
        float radius = distrib01(rng) * 0.5;
        balls.push_back(Ball(position, velocity, radius));
    }
    //balls.clear();
    if (0)
    {
        balls.push_back(Ball(sf::Vector2f(0.1, 0.5), sf::Vector2f(0.1, 0), 0.2));
        balls.push_back(Ball(sf::Vector2f(0.9, 0.5), sf::Vector2f(-0.1, 0), 0.2));
    }

    if (balls.empty())
    {
        cout << "meat balls can't be empty\n";
        exit(0);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        float dt = frameClock.restart().asSeconds();
        for (auto& ball : balls)
        {
            ball.update(dt);
        }
        int y = 0;
        int mn = (int)1e9, mx = -(int)1e9;
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < p; j++)
            {
                sf::Vector2f point(eps * i + eps / 2, eps * j + eps / 2);

                float dist = 0;
                for (auto& ball : balls)
                {
                    dist += Gauss(point, ball.position, ball.radius / 3) / Gauss({}, {}, ball.radius / 3);
                    //dist += max(0.0f, get_dist(point, ball.position) - ball.radius);
                }

                dist *= 255;

                int col = dist;

                mn = min(mn, col);
                mx = max(mx, col);
                col = min(col, 255);
                sf::Color color;
                if (col < 200)
                {
                    color = sf::Color(0, 0, 0);
                }
                else
                {
                    color = sf::Color(col, col, 255);
                }


                //sf::Color color = sf::Color(rng() % 256, rng() % 256, rng() % 256);
                varray[y++].color = color;
                varray[y++].color = color;
                varray[y++].color = color;
                varray[y++].color = color;
            }
        }

        if (secClock.getElapsedTime().asSeconds() >= 1)
        {
            cout << " : " << fixed << setprecision(10) << mn << " " << mx << ", fps = " << 1 / dt << "\n";
            secClock.restart();
        }


        window.clear();
        window.draw(varray);

        //window.draw(shp);
        window.display();

    }
    exit(0);
}

int main() {
    uniform_real_distribution<float> distrib01;

    vector<Ball> balls;
    for (int i = 0; i < 20; i++)
    {
        sf::Vector2f position = sf::Vector2f(distrib01(rng), distrib01(rng));
        sf::Vector2f velocity = sf::Vector2f(distrib01(rng), distrib01(rng)) * 0.5f;
        while (get_dist(velocity, sf::Vector2f(0, 0)) < 0.5)
        {
            velocity = sf::Vector2f(distrib01(rng), distrib01(rng)) * 0.5f;
        }
        velocity *= 2.0f;
        float radius = distrib01(rng) * 0.5;
        while (radius < 0.2)
        {
            radius = distrib01(rng) * 0.5;
        }
        radius *= 2;
        balls.push_back(Ball(position, velocity, radius));
    }
    //run();
    //exit(0);
    {
        mt19937 rng(228);
        uniform_real_distribution<float> distrib01(0, 1);
        for (int i = 0; i < 100; i++) {
            randoms[i] = distrib01(rng);
        }
    }
    if (!sf::Shader::isAvailable())
    {
        cout << "shaders are not available... (sad)!\n";
        // shaders are not available...
    }
    else
    {
        cout << "shaders are available... (happy)!\n";
    }

    sf::Shader shader;


    if (!shader.loadFromFile("Mihnea.frag", sf::Shader::Fragment))
    {
        cout << "Could not load \"NewShader.frag\"(sad)\n";
        // error...
    }
    else
    {
        cout << "load succesfull: \"NewShader.frag\"(happy)\n";
    }

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("dim", 1);


    sf::Font font;

    if (!font.loadFromFile("font.ttf")) {
        cout << "Couldn't load font!\n";
        exit(0);
    }

    float ela = 0;
    xc = 0;
    yc = 0;
    sz = 4;

    sf::RenderWindow window(sf::VideoMode(900, 900), "Trippy!");

    sf::Clock frameClock;

    sf::Texture txt;

    sf::RectangleShape rectFundal;
    rectFundal.setFillColor(sf::Color::Yellow);
    rectFundal.setPosition(sf::Vector2f(-0.5, -0.5));
    rectFundal.setSize(sf::Vector2f(1, 1));

    sf::RectangleShape shp;
    sf::View view;

    view.setSize(sf::Vector2f(1, 1));
    view.setCenter(sf::Vector2f(0, 0));

    window.setView(view);

    shp.setTexture(&txt);
    shp.setSize(sf::Vector2f(1, 1) * 0.7f);
    shp.setPosition(sf::Vector2f(0, 0) - shp.getSize() / 2.0f);

    long double dim = 2;

    sf::Clock glock;

    sf::Text text;

    sf::VertexArray varray1(sf::LinesStrip, 2);
    varray1[0].position = sf::Vector2f(-1, -1) * 0.01f;
    varray1[1].position = sf::Vector2f(+1, +1) * 0.01f;


    sf::VertexArray varray2(sf::LinesStrip, 2);
    varray2[0].position = sf::Vector2f(-1, +1) * 0.01f;
    varray2[1].position = sf::Vector2f(+1, -1) * 0.01f;

    for (int i = 0; i < 2; i++) {
        varray1[i].color = sf::Color(sf::Color(200, 20, 70));
        varray2[i].color = sf::Color(sf::Color(200, 20, 70));
    }

    sf::VertexArray geometriePentruShader(sf::Quads, 4);

    xc = 0;
    yc = 0;
    sz = 2;

    geometriePentruShader[0].texCoords = sf::Vector2f(0, 0);
    geometriePentruShader[1].texCoords = sf::Vector2f(0, 1);
    geometriePentruShader[2].texCoords = sf::Vector2f(1, 1);
    geometriePentruShader[3].texCoords = sf::Vector2f(1, 0);

    sf::FloatRect bounds = shp.getGlobalBounds();
    float left = bounds.left;
    float right = bounds.left + bounds.width;
    float top = bounds.top;
    float bottom = bounds.top + bounds.height;

    geometriePentruShader[0].position = sf::Vector2f(left, top);
    geometriePentruShader[1].position = sf::Vector2f(left, bottom);
    geometriePentruShader[2].position = sf::Vector2f(right, bottom);
    geometriePentruShader[3].position = sf::Vector2f(right, top);


    sf::Clock timeCeas;

    sf::Clock altCeas;

    bool upd = 1;

    shader.setUniformArray("randoms", randoms, 100);

    bool pressUp = 0, pressDown = 0, pressLeft = 0, pressRight = 0;
    mt19937 rng(777);
    float R = 0.1;
    uniform_real_distribution<float> distrib(-R, +R);

    sf::Clock cl;
    float noise = 0, rate = 0, deriv_rate = distrib(rng);
    while (window.isOpen()) {

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

        // convert it to world coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        float dt = frameClock.restart().asSeconds();
        for (auto& ball : balls)
        {
            ball.update(dt);
        }
        ela += dt;

        const float consume = 0.1;

        bool now_pressUp = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
        bool now_pressDown = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
        bool now_pressLeft = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
        bool now_pressRight = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                upd = 1;
                sz *= pow(0.9, event.mouseWheelScroll.delta);
            }
        }

        for (int i = 0; i < (int)balls.size(); i++)
        {
            ballposition[i] = balls[i].position;   
            ballradius[i] = balls[i].radius;
        }

        if (ela >= 0.1 && 0) {
            sz *= 0.9;
            upd = 1;
            ela = 0;
        }

        float speed = 0.1 * sz;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            speed *= 3;
        }

        if (!pressUp && now_pressUp) {
            yc -= speed;
            upd = 1;
        }

        if (!pressDown && now_pressDown) {
            yc += speed;
            upd = 1;
        }


        if (!pressLeft && now_pressLeft) {
            xc -= speed;
            upd = 1;
        }

        if (!pressRight && now_pressRight) {
            xc += speed;
            upd = 1;
        }

        pressUp = now_pressUp;
        pressDown = now_pressDown;
        pressLeft = now_pressLeft;
        pressRight = now_pressRight;

        ela += dt;
        sf::Text text;
        float num = 6.66;
        stringstream ss1;
        ss1 << "(" << fixed << setprecision(8) << xc << ", " << yc << ", " << sz << ")";
        text.setString(ss1.str());
        text.setFont(font);
        text.setScale(sf::Vector2f(1, 1) * 0.001f);
        text.setPosition(sf::Vector2f(-0.5, -0.5));

        if (upd) {
            upd = 0;
            geometriePentruShader[0].texCoords = sf::Vector2f(xc, yc) + sf::Vector2f(-sz, -sz) / 2.0f;
            geometriePentruShader[1].texCoords = sf::Vector2f(xc, yc) + sf::Vector2f(-sz, +sz) / 2.0f;
            geometriePentruShader[2].texCoords = sf::Vector2f(xc, yc) + sf::Vector2f(+sz, +sz) / 2.0f;
            geometriePentruShader[3].texCoords = sf::Vector2f(xc, yc) + sf::Vector2f(+sz, -sz) / 2.0f;
        }

        sf::CircleShape cr;
        cr.setRadius(0.1);
        cr.setOrigin(sf::Vector2f(1, 1) * cr.getRadius());



        cr.setPosition(worldPos);

        sf::Vector2f dif = worldPos;
        dif *= (float)sz / (float)0.7;
        dif += sf::Vector2f(xc, yc);

        noise += dt * rate;
        rate += dt * deriv_rate;

        if (cl.getElapsedTime().asSeconds() >= 1)
        {
            cl.restart();
            rate = distrib(rng);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            for (auto& it : balls)
            {
                //it.velocity += (dif - it.n) * dt * 10.0f;
            }
            //cout << "pressed\n";
        }

        shader.setUniform("position", dif);
        shader.setUniform("pressed", sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
        shader.setUniform("radius", (float)(sz * 0.1));
        shader.setUniform("time", altCeas.getElapsedTime().asSeconds());
        shader.setUniform("noise", noise);
        shader.setUniform("cnt_balls", (int)balls.size());
        shader.setUniformArray("ballposition", ballposition, 100);
        shader.setUniformArray("ballradius", ballradius, 100);



        window.clear();



        window.draw(rectFundal);
        window.draw(geometriePentruShader, &shader);
        text.setFillColor(sf::Color::Red);
        window.draw(text);
        window.draw(varray1);
        window.draw(varray2);

        sf::Clock u;
        window.display();
        float time_taken_to_draw = u.getElapsedTime().asSeconds();

        if (timeCeas.getElapsedTime().asSeconds() >= 1)
        {
            cout << "time_taken_to_draw = " << fixed << setprecision(6) << time_taken_to_draw << "\n";
            timeCeas.restart();
        }
    }

    return 0;
}