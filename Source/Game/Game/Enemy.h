class Enemy : public viper::Actor {  
public:  
    float speed = 200.0f;  
    float fireTimer = 0.0f;  
    float fireTime = 0.0f;

public:  
    Enemy() = default;  
    Enemy(const viper::Transform transform) :  
        Actor{ transform }  
    {}  

    void Update(float dt) override;  

    void OnCollision(Actor* other) override;  
};