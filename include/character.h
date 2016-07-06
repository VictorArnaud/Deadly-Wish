#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include "character_state.h"
#include "character_state_factory.h"
#include "util.h"

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;
using namespace ijengine;
using namespace util;


class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life);
	~Character();
    
    enum {
        START_MOVING_DOWN,
        START_MOVING_LEFT,
        START_MOVING_RIGHT,
        START_MOVING_UP, 
        STOP_MOVING_DOWN,
        STOP_MOVING_LEFT,
        STOP_MOVING_RIGHT,
        STOP_MOVING_UP,
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        DEFENSE,
        SPECIAL,
        NUMBER_OF_CHARACTER_EVENTS
    };


    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> direction() const;

    unsigned id() const { return m_id; }

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void change_character_state(State next_state);
    void handle_state();
    string choose_sprite_path(unsigned player_id);
    bool on_event(const GameEvent& event);
    virtual void heavy_attack() = 0;
    virtual void light_attack() = 0;
    virtual void defense() = 0;
    virtual void special() = 0;

    typedef enum {MOVING_RIGHT, MOVING_LEFT} MovingState;
    


protected:
    unsigned m_id;
    MovingState m_moving_state;
    CharacterState* m_state;
    CharacterStateFactory m_character_state_factory;
    int m_frame;
    int m_start;
    int m_w;
    int m_h;
    int m_life;
    int m_heavy_attack_cooldown;
    int m_light_attack_cooldown;
    int m_defense_cooldown;
    int m_special_cooldown;
    int m_last_used_heavy_attack;
    int m_last_used_light_attack;
    int m_last_used_defense;
    int m_last_used_special;
    bool m_freeze;
    double m_x_speed;
    double m_y_speed;
    double m_speed;
    vector< shared_ptr<Texture> > m_textures;
    unordered_map<string, pair<double, double> > m_speed_vector;
    Rectangle m_bounding_box;
    vector<string> m_sprite_paths;

    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif
