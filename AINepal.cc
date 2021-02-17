#include "Player.hh"
#include <queue>
#include <complex>
using namespace std;


/**
 * Write the name of your player and save this file
 * as AI<name>.cc
 */
#define PLAYER_NAME Nepal





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }
    

    /**
     * Attributes for your player can be defined here.
     */     
 vector<Dir> all_dirs;  //vector defined for all the directions.
 vector<Dir> all_re_dirs;
 typedef vector<vector<int>>graph;
 typedef complex<int> surrounding;
 vector<surrounding> all_surround;

void BFS_bonuses(graph &g ){
        queue <Pos> q;
        Pos p;
        int a , b;
        for(int i = 0;i < number_rows() ; ++i){
            for(int j = 0; j < number_window_columns() ; ++j ){
                a = i;
                b = j + round();
                b = b % number_universe_columns();

                p = {a , b};
                CType t = cell(p).type;
                if(within_window(p, round()+1) and (t == WATER_BONUS or t == MISSILE_BONUS or t == GAS_BONUS )){
                    g[a][b] = 0;
                    q.push(p);
                }
            }
        }
       while(not q.empty()){
            Pos current_pos = q.front();
            q.pop();
            for (surrounding s : all_surround){
                p = current_pos + s;
                int k = (second(p)+number_universe_columns()) % number_universe_columns();
                p = {first(p) , k};
                if (within_window(p, round())and( g[first(p)][second(p)] == -1 or g[first(p)][second(p)] > g[first(current_pos)][second(current_pos)] +1)) {
                    g[first(p)][second(p)] = g[first(current_pos)][second(current_pos)] +1;
                    q.push(p);
                }
            }
        }
    }



void BFS_avoid(graph &g ){
        Pos p;
        int a , b;
        for(int i = 0;i < number_rows() ; ++i){
            for(int j = 0; j < number_window_columns() ; ++j ){
                a = i;
                b = j + round();
                b = b % number_universe_columns();

                p = {a , b};
                CType t = cell(p).type;
                if(within_window(p, round()) and (t == TYRE or t == MISSILE or (t == CAR and player_of(cell(p).cid)!= me()))) {
                    g[a][b] = 0;
               }
            }
        }
    }

    /*bool not_collide(){
      for(Dir d: all_dirs){
        if ()
      }
    }
    */
    void car_forbidden(Pos p , Dir d , Car_Id cid , graph &g_avoid){
        if(d == DEFAULT){
            if(within_window(p , round() +1))g_avoid[first(p)][second(p)] = cid+100;
            if(within_window(p+SLOW_UP, round() +1))g_avoid[first(p)-1][second(p)] = cid+100;
            if(within_window(p+SLOW_DOWN , round() +1))g_avoid[first(p)+1][second(p)] = cid+100;
            if(within_window(p+DEFAULT , round() +1))  g_avoid[first(p)][second(p)+1] = cid+100;
            if(within_window(p+UP , round() +1)) g_avoid[first(p)-1][second(p)+1] = cid+100;
            if(within_window(p+DOWN , round() +1))  g_avoid[first(p)+1][second(p)+1] =cid+100;
            
        }
        else if(d==SLOW_UP or d == SLOW_DOWN){
            if(within_window(p , round() +1)) g_avoid[first(p)][second(p)] = cid+100;
            if(within_window(p+DEFAULT , round() +1)) g_avoid[first(p)][second(p)+1] = cid+100;
            if(within_window(p+FAST , round() +1))g_avoid[first(p)][second(p)+2] = cid+100;

        }
        
        else if(d == UP or d == DOWN){
            if(within_window(p , round() +1)) g_avoid[first(p)][second(p)] = cid+100;
            if(within_window(p+DEFAULT , round() +1)) g_avoid[first(p)][second(p)+1] = cid+100;
        }

    }
    
    void is_forbidden(Pos p , Dir d , graph &g_avoid ){
    if(d == DEFAULT){
        if(within_window(p+SLOW_UP, round() +1))g_avoid[first(p)-1][second(p)] = 0;
        if(within_window(p+SLOW_DOWN , round() +1))g_avoid[first(p)+1][second(p)] = 0;
        if(within_window(p+UP , round() +1))g_avoid[first(p)-1][second(p)+1] = 0;
        if(within_window(p+DEFAULT , round() +1))g_avoid[first(p)][second(p)+1] = 0;
        if(within_window(p+DOWN , round() +1))g_avoid[first(p)+1][second(p)+1] = 0;

    }
     else if (d == SLOW_UP or d == SLOW_DOWN){
        if(within_window(p+DEFAULT , round() +1))g_avoid[first(p)][second(p)+1] = 0;
        if(within_window(p+FAST , round() +1))g_avoid[first(p)][second(p)+2] = 0;

    }
    else if(d == UP or d == DOWN){
        if(within_window(p+DEFAULT , round() +1))g_avoid[first(p)][second(p)+1] = 0;
    }
    else if(d == FAST){
      if(within_window(p + SLOW_UP , round() +1))g_avoid[first(p)-1][second(p)] = 0;
      if(within_window(p + SLOW_DOWN , round() +1))g_avoid[first(p)+1][second(p)] = 0;
    }
}
    bool safe(Pos p){  //To protect from missile.
        complex<int> p1 = {0 , -2};
        if (within_window(p+p1 , round()+1) and cell(p + p1).type == MISSILE) return false;
        return true;
    }

    bool not_collide(Pos po , Car_Id my_cid){
      for (Dir d : all_re_dirs) {
        Pos po1 = po + d;
        int l = first(po1);
         int k = second(po1);
         k = k % number_universe_columns();
         po1 ={l , k};
         if(within_window(po1, round()) and cell(po1).type == CAR and cell(po1).cid != my_cid) return false;
    }
    return true;
  }

    /**
     * Play method.
     * 
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */     
    virtual void play () {
        if (round() == 0) {
      // All allowed directions // The vector all_dirs is previously defined.
      all_dirs ={SLOW ,SLOW_UP , SLOW_DOWN, DEFAULT , UP, DOWN,FAST,FAST_UP,FAST_DOWN};
      all_re_dirs={{0,0},{-1, 0},{1 , 0},{-1 ,-1},{0, -1},{1, -1},{-1, -2},{0, -2},{1 , -2}};

       all_surround ={ {-1 , -1 },{-1 , 0},{0 , -1},{1 , -1}, {1 , 0} ,{0 ,0}};
    }


    graph g_bonuses(number_rows(), vector<int>(number_universe_columns() , -1));
    BFS_bonuses(g_bonuses);

    graph g_avoid(number_rows(), vector<int>(number_universe_columns() , -1));   
    BFS_avoid(g_avoid);



for (Car_Id cid = begin(me()); cid != end(me()); ++cid) {

    Car c = car(cid);
    Pos po;
      
    if (c.alive) { // if the car is alive and


     po = c.pos;
    cerr << "Pos of car" << po << endl;
    int min = g_bonuses[first(po)][second(po)]; // To find the min one to move to.
    Dir aff = {0 , 1};




    Pos po1;
    for (Dir d : all_dirs) {
        po1 = po + d;
         int l = first(po1);
         int k = second(po1);
         k = k % number_universe_columns();
         po1 ={l , k};     //The exact position with the addded direction.
         if(within_window(po1, round()) and cell(po1).type == TYRE){
            
            is_forbidden(po1 , d , g_avoid);
         }
         if(within_window(po1, round()) and cell(po1).type == CAR){
            car_forbidden(po1 , d , cid , g_avoid);
         }
         if (within_window(po1, round()+1) and safe(po1) and g_avoid[first(po1)][second(po1)] != cid+100 and g_avoid[first(po1)][second(po1)] != 0 and not_collide(po1 , cid) and g_bonuses[first(po1)][second(po1)] <= min){// add the condition of bullet  // if the bonus is nearer then it's our target.
            min = g_bonuses[first(po1)][second(po1)];
            aff = d;
         }
    }
    cerr << "Dir it returned:" << aff << endl;
    cerr << endl;
    int x = (round()+number_window_columns()) % number_universe_columns();
    //if(second(po+aff)>= number_universe_columns()) move(cid,{0,0});
    if( (x-1 == second(po+aff) ) or x-2 == second(po+aff)) move(cid ,{0,0});
    else if(min >= 1 and c.nb_miss > 0 and ( ( (cell(po +DEFAULT).type == CAR and player_of(cell(po +DEFAULT).cid) != me() ) or (cell(po +FAST).type == CAR and player_of(cell(po +FAST).cid) != me())  or cell(po +DEFAULT).type == TYRE))) shoot(cid);
    else if ( within_window(po+SLOW_UP ,round()+1) and cell (po+SLOW_UP).type == TYRE and within_window(po+DEFAULT, round()+1) and cell(po+DEFAULT).type != TYRE)move(cid ,DEFAULT);
    else if(within_window(po+SLOW_DOWN , round()+1) and cell (po+SLOW_DOWN).type == TYRE and within_window(po+DEFAULT, round()+1) and cell(po+DEFAULT).type != TYRE)move(cid ,DEFAULT);
    else if(within_window(po+ aff , round()+1)) move(cid, aff);
    else {
    Dir d1 = all_dirs[randomize(0, all_dirs.size()-1)];
    if (within_window(c.pos + d1, round()+1)) move(cid, d1);
    else move(cid , {0,0});
    }
  
  }
}
  

}
    
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
