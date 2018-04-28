struct vt{
    int x,y;
    vt operator-(){return vt(-this->x,-this->y);}
    vt operator+(vt b){return {this->x+b.x,this->y+b.y};}
    vt operator-(vt b){return *this+(-b);}
    vt operator*(int b){return vt(this->x*b,this->y*b);}
    int operator*(vt b){return this->x*b.x+this->y*b.y;}
    vt operator/(int b){return vt(this->x/b,this->y/b);}
    int operator%(vt b){return this->x*b.y - b.x*this->y;}
    bool operator==(vt b){return this->x==b.x&&this->y==b.y;}
    bool operator!=(vt b){return !((*this)==b);}
    bool collinear(vt b){return (*this)%b==0;}
    bool opposite(vt b){return this->collinear(b)&&(*this)*b<0;}
    double length(){return sqrt(this->x*this->x+this->y*this->y);}
    int sqLength(){return this->x*this->x+this->y*this->y;}
    vt(){}
    vt(int x,int y):x(x),y(y){}
    vt(int x1,int y1,int x2,int y2):x(x2-x1),y(y2-y1){}
};
