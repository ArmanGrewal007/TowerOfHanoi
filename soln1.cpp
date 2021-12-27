# include <iostream>
# include <vector>
# include <cmath>
using namespace std;
////////////////////////// CUBE CLASS ///////////////////////////////////////
class Cube {
private:
    double length_;
public:
    Cube(double length) {length_ = length;} // Ctor
    void setLength(double length) {length_ = length;}
    double getLength() const {return length_;}
    double getVolume() const {return pow(length_, 3);}
    double getSurfaceArea() const {return 6 * pow(length_, 2);}
};
////////////////////////// STACK CLASS ///////////////////////////////////////
class Stack {
private:
    std::vector<Cube> cubes_;
public:
    void push_back(const Cube & cube) {
        // Ensure that we do not push a cube on top of a smaller cube:
        if ( size() > 0 && cube.getLength() > peekTop().getLength() ) {
            std::cerr << "A smaller cube cannot be placed on top of a larger cube." << std::endl;
            std::cerr << "  Tried to add Cube(length=" << cube.getLength() << ")" << std::endl;
            std::cerr << "  Current stack: " << *this << std::endl;

            throw std::runtime_error("A smaller cube cannot be placed on top of a larger cube.");
        }

    cubes_.push_back(cube);
    }

    Cube removeTop() {
        Cube cube = peekTop();
        cubes_.pop_back();
        return cube;
    }
    Cube & peekTop() {return cubes_[cubes_.size() - 1];}
    unsigned size() const {return cubes_.size();}

    // An overloaded operator<<, allowing us to print the stack via `cout<<`:
    friend std::ostream& operator<<(std::ostream & os, const Stack & stack);
};
std::ostream& operator<<(std::ostream & os, const Stack & stack) {
    for (unsigned i = 0; i < stack.size(); i++) {
        os << stack.cubes_[i].getLength() << " ";
    }
    os << endl;
    return os;
}


////////////////////////// GAME CLASS ///////////////////////////////////////
class Game {
private:
    std::vector<Stack> stacks_;
public:
    Game(){ // Default Ctor
        // Create the three empty stacks:
        for (int i = 0; i < 3; i++) {
            Stack stackOfCubes;
            stacks_.push_back(stackOfCubes);
        }

        // Create the four cubes, placing each on the [0]th stack:
        Cube a(4); stacks_[0].push_back(a);
        Cube b(3); stacks_[0].push_back(b);
        Cube c(2); stacks_[0].push_back(c);
        Cube d(1); stacks_[0].push_back(d);
    };

    void _move(unsigned index1, unsigned index2) {
        // Remove the cube from index1, and place it on index2
        Cube cube = stacks_[index1].removeTop();
        stacks_[index2].push_back(cube);
    }

    void _legalMove(unsigned index1, unsigned index2) {
        // If index2 has a cube and index1 is empty, move index2 -> index1
        if (stacks_[index1].size() == 0 && stacks_[index2].size() > 0) {
            _move(index2, index1);
        }
        // If index1 has a cube and index2 is empty, move index1 -> index2
        else if (stacks_[index1].size() > 0 && stacks_[index2].size() == 0) {
            _move(index1, index2);
        }
        // If both index1 and index2 have cubes,
        // If index1 has smaller cube, move index1 -> index2
        // If index2 has smaller cube, move index2 -> index1
        else if (stacks_[index1].size() > 0 && stacks_[index2].size() > 0) {
            if (stacks_[index1].peekTop().getLength() < stacks_[index2].peekTop().getLength()){
                _move(index1, index2);
            } 
            else {
                _move(index2, index1);
            }
        }
        cout << *this << endl;
    }

    void solve() {
        while (stacks_[2].size() != 4) {
            _legalMove(0, 1);
            _legalMove(0, 2);
            _legalMove(1, 2);
        }
    }

    // An overloaded operator<<, allowing us to print the stack via `cout<<`:
    friend std::ostream& operator<<(std::ostream & os, const Game & game);
};
std::ostream& operator<<(std::ostream & os, const Game & game) {
    for (unsigned i = 0; i < game.stacks_.size(); i++) {
        os << "Stack[" << i << "]: " << game.stacks_[i];
    }
    return os;
}


int main() {
  Game g;

  std::cout << "Initial game state: " << std::endl;
  std::cout << g << std::endl;

  g.solve();

  std::cout << "Final game state: " << std::endl;
  std::cout << g << std::endl;

  return 0;
}