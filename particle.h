/* Code concept from filmote thanks filmote
 * Pharap and MLXXXP helped too thanks!
 * 
 *  ARDUBOY FOREVER!
 * 
 * 
 */

#define boardWidth 5
#define boardHeight 10
#define boardOffset 47
#define partSize 6

struct Particle {

    private:

        int16_t x = 0;
        int16_t y = 0;
        float velx = 0;
        float vely = 0;
        uint8_t counterInit = 0;
        uint8_t counter = 0;
        uint8_t pSize = 1;
        uint8_t type = 1;
        int16_t boundL, boundR;
        uint8_t wordNum;

    public:

        static constexpr float rThresh = 0.000001 * 16;
        static constexpr float cF = 0.96;
        static constexpr float gravity = 0.12;

        int16_t getX()                          { return this->x; }
        int16_t getY()                          { return this->y; }
        int8_t getCounter()                     { return this->counter; }
        uint8_t getSize()                       { return this->pSize; }
        uint8_t getWord()                       { return this->wordNum; }
        uint8_t getType()                       { return this->type; }

        void setX(int16_t val)                  { this->x = val; }
        void setY(int16_t val)                  { this->y = val; }
        void setCounter(int16_t val)             { this->counter = val; this->counterInit = val; }
        void setVelX(float val)                  { this->velx = val; }
        void setVelY(float val)                  { this->vely = val; }
        void setSize(uint8_t val)                { this->pSize = val; }
        void setType(int val)                { this->type = val; }
        void setWord(int val)                { this->wordNum = val; } 

    public:

        void update() {
          

          // move your particle based on direction, whatever ..

          this->vely -= gravity * this->pSize;
          this->velx *= cF;

          if( this->type == 1 ){
            this->boundL = boardOffset+2;
            this->boundR = (boardWidth*partSize)+2+boardOffset;
          }
          else if( this->type ==0){
            this->boundL = 0;
            this->boundR = 128;
          }
          else if( this->type ==2){
            this->boundL = 0;  
            this->boundR = boardOffset;
          }
          else if( this->type ==3){
            this->boundL = (boardWidth*partSize)+boardOffset+4;  
            this->boundR = 128;
          }
                    
          if(this->x > this->boundR - this->pSize ){
            this->x = this->boundR - this->pSize ;
            this->velx = -this->velx;
            
          }
          if(this->x < this->boundL){
            this->x = this->boundL;
            this->velx = -this->velx;
          }
          
          if(this->y > (boardHeight*partSize)+4){ // above (below) board height - bottom of screen
            this->y = (boardHeight*partSize)+4;

            if(this->vely > rThresh)
              this->vely = -this->vely * rThresh;
            else
              this->vely = 0;
          }

          if( this->type ==2 || this->type ==3 ){
            // let stuff go negative yo
          }
          else{
             if(this->y < 0){ // below (above) board - top of screen
              if(this->vely > rThresh)
                this->vely = -this->vely * rThresh;
              else
                this->vely = 0;            
            }           
          }
          
          this->x += this->velx;
          this->y -= this->vely;

          // shift size
          
          if (this->counter < counterInit * 0.5 ){
            if( this->pSize > 2) this->pSize = 2;
          }
          if (this->counter <  counterInit * 0.2 ){
            if( this->pSize > 1) this->pSize = 1;
          }
          
          if (this->counter > 0) this->counter--;

        }

        bool render() {

            return (this->counter > 0);

        }

};
