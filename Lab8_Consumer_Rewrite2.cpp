#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
	
	//name of text file
	string textFile = argv[1];

	// Size of the shared memory in bytes.
	// Preferably a power of 2
	// This line of code assigns the size to be
	// 1024 bytes or 1KB
	int shmSize = atoi(argv[2]);

	// -- Semaphore and Shared Memory Initialization --

	// Semaphore set ID
	int semID;

	// Id for the shared memory
	int shmID;
	int fID;

	// 1 key = 1 semaphore set (or array)
	// Think of it like a map (the data structure)
	// Put a large constant here, e.g. 1234
	key_t semKey = 1234;

	// 1 key = 1 shared memory segment
	// Think of a map (the data structure)
	key_t shmKey = 1234;

	key_t fKey = 1235;

	// Access file
	ofstream myFile(textFile.c_str(), ios::out | ios::trunc);

	// Flags to use upon getting the semaphore set.
	// Normally when dealing with flags, you usually bitwise-OR
	// flags together.
	// IPC_CREAT - If no existing semaphore set is associated with the key, create one
	// 0666 - Remember chmod? The 0 in front specifies that the number is in octal
	int semFlag = IPC_CREAT | 0666;

	// Number of semaphores in the semaphore set
	// For this example, we'll just create 1 semaphore set
	int nSems = 2;

	// Attempt to get a semaphore set
	// Returns -1 if there was an error.
	semID = semget(semKey, nSems, semFlag);
	if( semID == -1 ) {

		perror( "semget" );
		exit( 1 );

	}

	// Flags + permissions when creating the shared
	// memory segment.
	// IPC_CREAT - If the shared memory does not exist yet, automatically create it
	// 0666 - Remember chmod? The 0 in front indicates that the number is expressed in octal.
	int shmFlags = IPC_CREAT | 0666;

	// Pointer for the starting address of the shared memory segment.
	char* sharedMem;

	int* f;

	// Yes, this is almost the same as semget()
	shmID = shmget(shmKey, shmSize, shmFlags);

	// shmat() returns the starting address of the shared memory
	// segment, so we assign it to sharedMem.
	sharedMem = (char*) shmat(shmID, NULL, 0);

	fID = shmget(fKey, 1, shmFlags);
	f = (int*) shmat(fID, NULL, 0);

	if( ((int*)sharedMem) == (int*)-1 || ((int*)f) == (int*)-1) {

		perror( "shmop: shmat failed" );

	} else {

		while (true) {

			// -- Semaphore Accessing --

			// Perform 2 operations
			int nOperations = 2;

			// Create an array of size 2 to hold
			// the operations that we will do on the semaphore set
			struct sembuf sema[nOperations];

			// Definition for the first operation
			// Our first operation will be to wait for the
			// semaphore to become 0
			sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
			sema[0].sem_op = 0; // Wait if semaphore != 0
			sema[0].sem_flg = SEM_UNDO; // See slides

			// Definition for the second operation
			sema[1].sem_num = 0; // Use the first semaphore in the semaphore set
			sema[1].sem_op = 1; // Increment semaphore by 1
			sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT; // See slides

			// Perform the operations that we defined.
			// Will return -1 on error.
			int opResult = semop( semID, sema, nOperations );

			// If we successfully incremented the semaphore,
				// we can now do stuff.
			if(opResult != -1) {
				
				//printf( "Successfully incremented semaphore!\n" );

				// read from shared memory
				char *buffer = new char[shmSize + 1]; //dynamic array
				strcpy(buffer, sharedMem);
				buffer[shmSize] = '\0';
				cout << buffer << endl;
				myFile << buffer;

				// -- Semaphore Releasing --

				// Set number of operations to 2
				nOperations = 2;

				// Modify the first operation such that it
				// now decrements the semaphore.
				sema[0].sem_num = 0; // Use the first semaphore in the semaphore set
				sema[0].sem_op = -1; // Decrement semaphore by 1
				sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

				sema[1].sem_num = 1; // Use the second semaphore in the semaphore set
				sema[1].sem_op = -1; // Decrement semaphore by 1
				sema[1].sem_flg = IPC_NOWAIT;

				opResult = semop( semID, sema, nOperations );
				if(opResult == -1) {

					perror("semop (decrement)");
					
				}
			
			} else {

				perror("semop (increment)");

			}

			//To give the other program a chance to gain control of the semaphore
			sleep(1);

			if (*f != 0) {

				break;
				
			}
		}

		myFile.close();

	}

	cout << "Done" << endl;
	return 0;

}