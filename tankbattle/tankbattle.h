#include <SDL2/SDL.h>

// pixels per frame
#define TANK_SPEED 0.75
#define BULLET_SPEED 2
// number of frames
#define SHOT_RELOAD 90
#define FPS 60

enum movement {
        NONE = 0,
        FORWARD = 1,
        BACKWARD = -1,
        RIGHT = 1,
        LEFT = -1,
};

// hold origin as SDL_Point ?
struct tank_state {
        SDL_FRect pos;
        int rotation_deg;
        enum movement move_direction;
        enum movement rotation_direction;
};

// save fired position? 
// if tank gun is shorter than tank body, 
// bullet would be within tank rectangle boundaries initially.
// That would count as collision, right now bullet initial pos
// is set outside tank rectangle.
struct bullet_state {
        SDL_FRect pos;
        int rotation_deg;
};

struct game_state {
        SDL_Texture *textures[2];
        struct tank_state tanks[2];
        // 8 bullets limit according to 
        // - bullet speed
        // - arena size
        // - number of players
        struct bullet_state bullets[8];
        char flying_bullets_num;
};

void move(struct game_state* state);

// engine stuff -- this is gonna be reorganized as header only library

struct line {
        float x1, y1, x2, y2;
};


void print_vertices(SDL_FPoint v[4]) {
        for (int i = 0; i < 4; i++) {
                printf("%d: (%f, %f) ", i, v[i].x, v[i].y);
        }
        printf("\n");
}

void print_line(struct line l, char id[]) {
        printf("%s : (%f, %f) (%f, %f)\n", id, l.x1, l.y1, l.x2, l.y2);
}

void as_vertices(SDL_FRect rect, SDL_FPoint vertices[4]) {
        vertices[0] = (SDL_FPoint) {rect.x, rect.y};
        vertices[1] = (SDL_FPoint) {rect.x + rect.w, rect.y};
        vertices[2] = (SDL_FPoint) {rect.x + rect.w, rect.y + rect.h};
        vertices[3] = (SDL_FPoint) {rect.x, rect.y + rect.h};
}

void as_lines(SDL_FPoint points[4], struct line lines[4]) {
        for (int i = 0; i < 4; i++) {
                SDL_FPoint p1 = points[i];
                SDL_FPoint p2 = points[(i + 1) % 4];
                lines[i] = (struct line) {p1.x, p1.y, p2.x, p2.y};
        }
}

SDL_FPoint rotate(SDL_FPoint p, SDL_FPoint center, int degrees) {
        double angle = degrees * M_PI / 180;
        SDL_FPoint p1 = {      
                center.x + (p.x - center.x) * cos(angle) - (p.y - center.y) * sin(angle),
                center.y + (p.x - center.x) * sin(angle) + (p.y - center.y) * cos(angle),
        };
        return p1;
}

SDL_bool check_line_intersection(struct line line1, struct line line2) {
        float s1_x, s1_y, s2_x, s2_y;
        s1_x = line1.x2 - line1.x1;     
        s1_y = line1.y2 - line1.y1;
        s2_x = line2.x2 - line2.x1;     
        s2_y = line2.y2 - line2.y1;
        float s, t;
        s = (-s1_y * (line1.x1 - line2.x1) + s1_x * (line1.y1 - line2.y1)) / (-s2_x * s1_y + s1_x * s2_y);
        t = ( s2_x * (line1.y1 - line2.y1) - s2_y * (line1.x1 - line2.x1)) / (-s2_x * s1_y + s1_x * s2_y);
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
                return SDL_TRUE;
        }
        return SDL_FALSE;
}

SDL_bool check_collision(SDL_FRect r1, int r1_r_degrees, SDL_FRect r2, int r2_r_degrees) {
        SDL_FPoint r1_vertices[4];
        as_vertices(r1, r1_vertices);
        SDL_FPoint r1_center = {r1.x + r1.w / 2, r1.y + r1.h / 2};
        SDL_FPoint r2_vertices[4];
        as_vertices(r2, r2_vertices);
        SDL_FPoint r2_center = {(r2.x + r2.w) / 2, (r2.y + r2.h) / 2};
        for (int i = 0; i < 4; i++) {
                r1_vertices[i] = rotate(r1_vertices[i], r1_center, r1_r_degrees);
                r2_vertices[i] = rotate(r2_vertices[i], r2_center, r2_r_degrees);
        }
        struct line r1_lines[4];
        struct line r2_lines[4];
        as_lines(r1_vertices, r1_lines);
        as_lines(r2_vertices, r2_lines);
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                        if (check_line_intersection(r1_lines[i], r2_lines[j])) {
                                return SDL_TRUE;
                        }
                }
        }
        return SDL_FALSE;
}
