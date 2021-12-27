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

    // Move a Cube from Stack `s1` to Stack `s2`:
    void _moveCube(Stack & s1, Stack & s2) {
        Cube cube = s1.removeTop();
        s2.push_back(cube);
    }

    // Move the cubes in the range [start...end] from `source` to `target`, using spare as a spare spot:
    void _move(
    unsigned start, unsigned end,
    Stack & source, Stack & target, Stack & spare,
    unsigned depth
    ) {
        cout << "Planning (depth=" << depth++ << "): Move [" << start << ".." << end << "] from Stack@" << &source << " -> Stack@" << &target << ", Spare@" << &spare << "]" << endl;

        // Check if we are only moving one cube:
        if (start == end) {
            // If so, move it directly:
            _moveCube( source, target );
            cout << *this << endl;
        } else {
            // Otherwise, use our move strategy:
            _move(start + 1, end  , source, spare , target, depth);
            _move(start    , start, source, target, spare , depth);
            _move(start + 1, end  , spare , target, source, depth);
        }
    }

    void solve() {
        _move(
            0, stacks_[0].size() - 1,  //< Move the entire set of cubes, [0 .. size-1]
            stacks_[0], //< Source stack is [0]
            stacks_[2], //< Target stack is [2]
            stacks_[1], //< Spare stack is [1]
            0   //< Initial depth (for printouts only) is 0
        );
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