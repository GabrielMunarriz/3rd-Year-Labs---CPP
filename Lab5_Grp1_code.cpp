#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

//Point3D Struct
struct Point3D {

    int x;
    int y;
    int z;

    Point3D(){ //default constructor
       x = 0;
       y = 0;
       z = 0;
    }

    Point3D(int x, int y, int z){ //constructor
       this->x = x;
       this->y = y;
       this->z = z;
    }

};

//Calculate Manhattan Distance Function
int findManhattanDistance(Point3D point1, Point3D point2){

    int deltaX = abs(point1.x - point2.x);
    int deltaY = abs(point1.y - point2.y);
    int deltaZ = abs(point1.z - point2.z);

    int manhattanDistance = deltaX + deltaY + deltaZ;
    
    return manhattanDistance;
}

//Main
int main (void) {

    //cin is temporarily placed in input
    string input;

    //Stores all points and manhattan distances dynamically
    vector<Point3D> pointsVector;

    //Finds the number of test cases
    getline(cin, input);
    int numberOfTestCases = stoi(input);

    for(int i = 0; i <= numberOfTestCases-1; i++) {

        //Clear the pointsVector at the start of each test case
        pointsVector.clear();

        //Find the number of points in a test case
        getline(cin, input);
        int numberOfPoints = stoi(input);

        //Creating new points and adding them into the pointArray
        for(int i = 0; i <= numberOfPoints-1; i++) {

            //Finding the values of coordinates
            getline(cin, input, ' ');
            int xCoordinate = stoi(input);
            getline(cin, input, ' ');
            int yCoordinate = stoi(input);
            getline(cin, input);
            int zCoordinate = stoi(input);

            pointsVector.push_back(Point3D(xCoordinate, yCoordinate, zCoordinate));
            
            //cout << pointVector[i].x << pointVector[i].y << pointVector[i].z << endl;

        }

        // Printing out the contents of pointsVector for each test case. Used for debugging purposes.
        // for(int i = 0; i <= numberOfPoints-1; i++){
        //     cout << pointsVector[i].x << " " << pointsVector[i].y << " " << pointsVector[i].z << endl;
        // }

        for(int i = 0; i <= numberOfPoints-2; i++){
            cout << findManhattanDistance(pointsVector[i], pointsVector[i+1]) << endl;
        }

        cout << " " << endl;

    }

    return 0;

}