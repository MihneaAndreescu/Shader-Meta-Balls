uniform sampler2D texture;
uniform float time;
uniform float radius;
uniform vec2 position;
uniform int cnt_balls;
uniform vec2[100] ballposition;
uniform float[100] ballradius;

float distance_squared(vec2 v, vec2 w) 
{
    return dot(v - w, v - w);
}

float distance(vec2 v, vec2 w) 
{
    return sqrt(dot(v - w, v - w));
}

float minimum_distance(vec2 v, vec2 w, vec2 p) 
{
    float l2 = distance_squared(v, w); 
    if (l2 == 0.0) 
    {
        return distance(p, v);
    }
    float t = max(0, min(1, dot(p - v, w - v) / l2));
    vec2 projection = v + t * (w - v);
    return distance(p, projection);
}

float trapez(vec2 a, vec2 b)
{
    return (a.x - b.x) * (a.y + b.y);
}

float trapez(vec2 a, vec2 b, vec2 c)
{
    return trapez(a, b) + trapez(b, c) + trapez(c, a);
}

float get_area(vec2 a, vec2 b, vec2 c)
{
    return abs(trapez(a, b, c)) * 0.5;
}

bool is_inside(vec2 a, vec2 b, vec2 c, vec2 p)
{
    float rl = get_area(a, b, c);
    float e = 0;
    e += get_area(a, b, p);
    e += get_area(a, c, p);
    e += get_area(b, c, p);
    float dif = abs(rl - e);
    return dif < 1e-5;
}

float minimum_distance(vec2 a, vec2 b, vec2 c, vec2 p) 
{
    if (is_inside(a, b, c, p))
    {
        return -min(minimum_distance(a, b, p), min(minimum_distance(a, c, p), minimum_distance(b, c, p)));
    }
    else
    {
        return min(minimum_distance(a, b, p), min(minimum_distance(a, c, p), minimum_distance(b, c, p)));
    }
}

vec2 rotate(vec2 a, float angle) 
{
    float x = a.x, y = a.y;
    float _cos = cos(angle), _sin = sin(angle);
    return vec2(x * _cos - y * _sin, x * _sin + y * _cos);
}

vec2 rotate(vec2 origin, vec2 a, float angle)
{
    return origin + rotate(a - origin, angle);
}

vec4 pixel;

struct Triangle
{
    vec2 a;
    vec2 b;
    vec2 c;
};

Triangle rotate(Triangle t, vec2 origin, float angle)
{
    t.a = rotate(origin, t.a, angle);
    t.b = rotate(origin, t.b, angle);
    t.c = rotate(origin, t.c, angle);
    return t;
}

void drawTriangle(Triangle t)
{
    if (minimum_distance(t.a, t.b, t.c, gl_TexCoord[0].xy) <= 1e-2)
    {
        pixel.b = 1;
    }
    float d = minimum_distance(t.a, t.b, t.c, gl_TexCoord[0].xy);
    if (1e-2 <= d && d <= 1e-1)
    {
        pixel.r = sin(d * 3e2);
        pixel.g = sin((d + 11) * (3e2 + 533));
        //pixel.g = sin((d + 11) * 1e2);
        //pixel.b = sin((d + 20) * 1e2);
    }
}


const float pi = 3.141592653589793;

float Gauss(vec2 point, vec2 origin, float sigma) 
{
    const float sq2pi = sqrt(2 * pi);
    point -= origin;
    float x = point.x, y = point.y;
    return 1 / (sigma * sq2pi) * exp(-(x * x + y * y) / (2 * sigma * sigma));
}
      

void main()
{
    pixel = texture2D(texture, gl_TexCoord[0].xy);

    float dist = 0;
    for (int i = 0; i < cnt_balls; i++)
    {
        dist += Gauss(gl_TexCoord[0].xy, ballposition[i], ballradius[i] / 3) / Gauss(vec2(0, 0), vec2(0, 0), ballradius[i] / 3);
    }
    float distinit = dist * 0.5;
    dist *= 255;
    int col = int(dist);

    col = min(col, 255);

    if (0)
    {
        pixel.r = pixel.g = pixel.b = 0;
    }
    else
    {   
        pixel.r = distinit * abs(sin(3.0 * (distinit + time) + 3.1 * 0));
        pixel.g = distinit * abs(sin(3.1 * (distinit + time) + 3.2 * 0));
        pixel.b = distinit * abs(sin(3.2 * (distinit + time) + 3.3 * 0));
    }
    
    gl_FragColor = gl_Color * pixel;
    return;
    for (int c = 0; c <= 3; c++)
    {
        if (minimum_distance(position, rotate(position, position + vec2(1, 1), time + (pi / 2) * c), gl_TexCoord[0].xy) <= 1e-1)
        {
            pixel.r = 1;
        }
    }


    float d = distance(position, gl_TexCoord[0].xy);
    if (d <= 0.2)
    {
        pixel.r = 1;
    }
   
    Triangle t = Triangle(vec2(0, 0), vec2(0.5, 0.3), vec2(0, 0.2));
    
    t = rotate(t, vec2(0, 0), time * 3);
    t = rotate(t, vec2(0, -1), time * 2);
    drawTriangle(t);
    
        
    


   // pixel.g = dot( gl_TexCoord[0].xy,  gl_TexCoord[0].xy);
    
    /*
    float x = gl_TexCoord[0].x;
    float y = gl_TexCoord[0].y;
    if (y >= sin(x * 10 + time) * 0.1 + noise) 
    {
        pixel.b = 1;
    }
    else
    {
    

    }*/
    gl_FragColor = gl_Color * pixel;
}