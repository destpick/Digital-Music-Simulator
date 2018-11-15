#include "header.h"

/*
* This function creates a node and fills it with the song information
* @param info: a record node filled with information on an individual song
* @returns a node fill with the song information
*/
Node *fill_record(Record info)
{
	// Creates a node
	Node * head = NULL;

	// Allocates the correct size of the Node
	head = (Node *)malloc(sizeof(Node));

	// Make sure that the head is not NULL
	if (head != NULL)
	{
		// Parses the information
		head->mNext = NULL;
		head->mPrevious = NULL;
		strcpy(head->mmSong.mArtist, info.mArtist);
		strcpy(head->mmSong.mAlbum, info.mAlbum);
		strcpy(head->mmSong.mSong, info.mSong);
		strcpy(head->mmSong.mGenre, info.mGenre);
		head->mmSong.mTime.mMin = info.mTime.mMin;
		head->mmSong.mTime.mSec = info.mTime.mSec;
		head->mmSong.mNumberOfTimesPlayed = info.mNumberOfTimesPlayed;
		head->mmSong.mRating = info.mRating;
	}

	return head;
} // end of definition of makeNode

/*
* Parse a single song line from the musicPlayList.csv
* @param line: a single song
* @returns a record
*/
Record import_line(char line[]) 
{
	char * value, * duration;
	char duplicate[100] = "";
	Record mmSong;
	char name[25];
	char *temp = NULL;
	int length = strlen(line);
	strcpy(duplicate, line);

	value = strtok(duplicate, "\"");

	if (strlen(value) == length) {
		strcpy(duplicate, line);
		value = strtok(duplicate, ",");

		strcpy(mmSong.mArtist, value);
	}
	else {
		strcpy(mmSong.mArtist, value);
	}
	value = strtok(NULL, ",");
	strcpy(mmSong.mAlbum, value);
	value = strtok(NULL, ",");
	strcpy(mmSong.mSong, value);
	value = strtok(NULL, ",");
	strcpy(mmSong.mGenre, value);
	duration = strtok(NULL, ",");
	value = strtok(NULL, ",");
	mmSong.mNumberOfTimesPlayed = (int)strtod(value, &temp);
	value = strtok(NULL, ",");
	mmSong.mRating = (int)strtod(value, &temp);
	mmSong.mTime = import_length(duration);
	return mmSong;
}

Duration import_length(char *length) {
	Duration mSongT;
	int min = 0, sec = 0;
	char *temp, *duplication;

	char mMin[10];

	strcpy(mMin, length);
	duplication = mMin;

	strcat(duplication, ":");

	min = (int)strtod(strtok(duplication, ":"), &temp);
	sec = (int)strtod(strtok(NULL, ":"), &temp);

	mSongT.mMin = min;
	mSongT.mSec = sec;

	return mSongT;
}

void insert_at_front(Node **rList, Record info) {
	Node *temp = NULL, *last = NULL, *prev = NULL;

	temp = fill_record(info);

	if (*rList == NULL) {
		(*rList) = temp;
		mNumOfSongs += 1;
	}
	else {
		last = *rList;
		prev = temp;
		prev->mNext = last;
		last->mPrevious = prev;
		prev->mPrevious = NULL;
		*rList = prev;
		mNumOfSongs += 1;
	}
}

void store_song(Node *rList, FILE *output) {
	char*value = NULL;
	char mArtistName[50];
	char * firstName;
	char *lastName;

	if (rList != NULL) {
		while (rList->mNext != NULL) {
			rList = rList->mNext;
		}
		while (rList != NULL) {
			if (strstr(rList->mmSong.mArtist, ",") == NULL) {
				fprintf(output, "%s, %s, %s %s, %d:%d, %d, %d", rList->mmSong.mArtist, rList->mmSong.mAlbum, rList->mmSong.mSong, rList->mmSong.mGenre, rList->mmSong.mTime.mMin, rList->mmSong.mTime.mSec, rList->mmSong.mNumberOfTimesPlayed, rList->mmSong.mRating);
			}
			else {
				strcpy(mArtistName, rList->mmSong.mArtist);
				strcat(mArtistName, ",");
				lastName = strtok(mArtistName, ",");
				firstName = strtok(NULL, ",");
				fprintf(output, " \" %s, %s \", %s, %s %s, %d:%d, %d, %d", lastName, firstName, rList->mmSong.mAlbum, rList->mmSong.mSong, rList->mmSong.mGenre, rList->mmSong.mTime.mMin, rList->mmSong.mTime.mSec, rList->mmSong.mNumberOfTimesPlayed, rList->mmSong.mRating);
			}
			if (rList->mPrevious != NULL) {
				fprintf(output, "\n");
			}
			rList = rList->mPrevious;
		}
	}
}

void display_by_song(Node *rList) {
	printf("\t\tmSongs in this Library: \n \n");

	while (rList != NULL) {
		printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
			rList->mmSong.mArtist, rList->mmSong.mSong, rList->mmSong.mAlbum, rList->mmSong.mTime.mMin, rList->mmSong.mTime.mSec,
			rList->mmSong.mGenre, rList->mmSong.mNumberOfTimesPlayed, rList->mmSong.mRating);
		rList = rList->mNext;
	}
}

void display_by_artist(Node *rList, char *mArtist) {
	int matches = 0;
	printf("mSongs by %s: ", mArtist);

	while (rList != NULL) {
		if (strcpy(rList->mmSong.mArtist, mArtist) == 0) {
			printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
				rList->mmSong.mArtist, rList->mmSong.mSong, rList->mmSong.mAlbum, rList->mmSong.mTime.mMin, rList->mmSong.mTime.mSec,
				rList->mmSong.mGenre, rList->mmSong.mNumberOfTimesPlayed, rList->mmSong.mRating);
			matches++;
		}
		rList = rList->mNext;
	}

	if (matches == 0) {
		printf("Sorry! No mSongs found by %s\n", mArtist);
	}
}

void edit_song_by_artist_name(Node **list, char *mArtist) {
	char charValue[50] = "";
	int intValue = 0, choice = 0, counter = 0;

	int edited = 0;

	Node * temp;
	temp = *list;

	while ((*list) != NULL || choice != 1) {
		if (strcmp((*list)->mmSong.mArtist, mArtist) == 0) {

			printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
				(*list)->mmSong.mArtist, (*list)->mmSong.mSong, (*list)->mmSong.mAlbum, (*list)->mmSong.mTime.mMin, (*list)->mmSong.mTime.mSec,
				(*list)->mmSong.mGenre, (*list)->mmSong.mNumberOfTimesPlayed, (*list)->mmSong.mRating);
			do {
				printf("Would you like to edit? Yes=1 and No=2");
				scanf("%d", &choice);
			} while (choice != 1 && choice != 2);
			if (choice == 1) {
				do {
					system("cls");
					printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
						(*list)->mmSong.mArtist, (*list)->mmSong.mSong, (*list)->mmSong.mAlbum, (*list)->mmSong.mTime.mMin, (*list)->mmSong.mTime.mSec,
						(*list)->mmSong.mGenre, (*list)->mmSong.mNumberOfTimesPlayed, (*list)->mmSong.mRating);
					printf("\nEnter the field you would like to edit. \n(1.) mArtist\n(2.) mSong Title\n(3.) mGenre\n(4.) mRating\n");
					scanf("%d", &choice);
				} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
				system("cls");
				switch (choice) {
				case 1:
					printf("Edit the name of mArtist: \n");
					scanf(" %99[^\n]", &charValue);
					strcpy((*list)->mmSong.mArtist, charValue);
					edited = 1;
					break;
				case 2:
					printf("Edit the name of the mSong title: \n");
					scanf(" %99[^\n]", &charValue);
					strcpy((*list)->mmSong.mSong, charValue);
					edited = 1;
					break;
				case 3:

					printf("Edit the name of the mGenre: \n");
					scanf(" %99[^\n]", &charValue);
					strcpy((*list)->mmSong.mGenre, charValue);
					edited = 1;
					break;

				case 4:
					do {
						system("cls");
						printf("Edit the mRating: \n");
						scanf("%d", &intValue);
					} while (intValue != 1 && intValue != 2 && intValue != 2 && intValue != 5);
					(*list)->mmSong.mRating = intValue;
					edited = 1;
					break;
				default:
					break;
				}
				system("cls");
				printf("Saving as: \n");
				printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
					(*list)->mmSong.mArtist, (*list)->mmSong.mSong, (*list)->mmSong.mAlbum, (*list)->mmSong.mTime.mMin, (*list)->mmSong.mTime.mSec,
					(*list)->mmSong.mGenre, (*list)->mmSong.mNumberOfTimesPlayed, (*list)->mmSong.mRating);

			}
			counter++;
		}
		if (edited == 1 || (*list)->mNext == NULL) {
			break;
		}
		*list = (*list)->mNext;
	}
	if (counter == 0) {
		printf("No matches found. \n");
	}
	*list = temp;
}

void edit_rating_by_artist_name(Node **list, char *mArtist) {
	int intValue = 0, choice = 0, counter = 0;

	int edited = 0;

	Node * temp;
	temp = *list;

	while ((*list) != NULL || choice != 1) {
		if (strcmp((*list)->mmSong.mArtist, mArtist) == 0) {

			printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
				(*list)->mmSong.mArtist, (*list)->mmSong.mSong, (*list)->mmSong.mAlbum, (*list)->mmSong.mTime.mMin, (*list)->mmSong.mTime.mSec,
				(*list)->mmSong.mGenre, (*list)->mmSong.mNumberOfTimesPlayed, (*list)->mmSong.mRating);
			do {
				printf("Would you like to edit? Yes=1 and No=2");
				scanf("%d", &choice);
			} while (choice != 1 && choice != 2);
			if (choice == 1) {
				do {
					system("cls");
					printf("Edit the mRating: \n");
					scanf("%d", &intValue);
				} while (intValue != 1 && intValue != 2 && intValue != 2 && intValue != 5);
				(*list)->mmSong.mRating = intValue;
				edited = 1;
				system("cls");
				printf("Saving as: \n");
				printf("mArtist: %s\nmSong Title: %s\nmAlbum Title: %s\nDuration: %d:%d\nmGenre: %s\nNumber of Plays: %d\nmRating: %d\n\n",
					(*list)->mmSong.mArtist, (*list)->mmSong.mSong, (*list)->mmSong.mAlbum, (*list)->mmSong.mTime.mMin, (*list)->mmSong.mTime.mSec,
					(*list)->mmSong.mGenre, (*list)->mmSong.mNumberOfTimesPlayed, (*list)->mmSong.mRating);

			}
			counter++;
		}
		if (edited == 1 || (*list)->mNext == NULL) {
			break;
		}
		*list = (*list)->mNext;
	}
	if (counter == 0) {
		printf("No matches found. \n");
	}
	*list = temp;
}


void play_all_songs(Node *rList) {
	while (rList != NULL) {
		printf("Now playing : ");
		printf(" %s, %s,%s,%s,%d:%d,%d,%d \n", rList->mmSong.mArtist, rList->mmSong.mAlbum, rList->mmSong.mSong, rList->mmSong.mGenre, rList->mmSong.mTime.mMin, rList->mmSong.mTime.mSec, rList->mmSong.mNumberOfTimesPlayed, rList->mmSong.mRating);
		rList->mmSong.mNumberOfTimesPlayed = rList->mmSong.mNumberOfTimesPlayed + 1;
		rList = rList->mNext;
		system("pause");
		system("cls");
	}
	system("cls");
}


void add_record(Node ** rList) {

	//fix the insert at front aspect of code//
	Record info = { "","","","",0,0,0,0 };
	char mArtistName[100] = "", mSongName[100] = "", gener[100] = "", mAlbumTime[100] = "";

	printf("Please enter the mArtist: \n");
	scanf(" %99[^\n]", mArtistName);
	strcpy(info.mArtist, mArtistName);

	printf("Please enter the mSong: \n");
	scanf(" %99[^\n]", mSongName);
	strcpy(info.mSong, mSongName);

	printf("Please enter the mGenre: \n");
	scanf(" %99[^\n]", gener);
	strcpy(info.mGenre, gener);

	printf("Please enter mAlbum name: \n");
	scanf(" %99[^\n]", mAlbumTime);
	strcpy(info.mAlbum, mAlbumTime);

	printf("Please enter the length of mSong (with a space): \n");
	scanf("%d %d", &info.mTime.mMin, &info.mTime.mSec);

	printf("Please enter your mRating (1-5): \n");
	scanf("%d", &info.mRating);

	info.mNumberOfTimesPlayed = 0;

	insert_at_front(*(&rList), info);
}


void remove_song_from_list(Node ** rList, char * mSong) {
	Node * temp = NULL, *prev = NULL, *head = NULL;
	int successful = 0;

	temp = *rList;
	head = *rList;

	while ((*rList) != NULL) {
		if (strcmp((*rList)->mmSong.mSong, mSong) == 0) {
			if (temp->mNext != NULL) {
				if (prev != NULL) {
					prev->mNext = temp->mNext;
					*rList = head;
					free(temp);
					successful = 1;
					mNumOfSongs--;
				}
				else {
					*rList = (*rList)->mNext;
					free(temp);
					head = NULL;
					mNumOfSongs--;
					successful = 1;
				}
			}
			else {
				prev->mNext = NULL;
				*rList = head;
				free(temp);
				successful = 1;
				mNumOfSongs--;
			}
			if (successful == 1) {
				break;
			}
		}
		if ((*temp).mNext != NULL) {
			prev = temp;
			*rList = (*rList)->mNext;
			temp = *rList;
		}
		else {
			*rList = (*rList)->mNext;
		}
	}
	*rList = head;
	if (successful == 0) {
		printf(" %s was not found! \n", mSong);
	}
}

void sort_menu(Node **list) {

	int choice = 0;
	do {
		system("cls");
		printf("(1) Sort by mArtist \n (2) Sort by mAlbum \n (3) Sort by mRating\n (4) Sort by times played \n");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	if (choice == 1) {

		sort_based_off_artist_name(list, mNumOfSongs);
	}
	else if (choice == 2) {
		sort_based_off_album(list, mNumOfSongs);
	}
	else if (choice == 3) {

		sort_based_of_rating(list, mNumOfSongs);
	}
	else if (choice == 4) {
		sort_based_off_number_of_times_played(list, mNumOfSongs);
	}
	printf(" Your library:  \n");
	display_by_song(*list);

	system("pause");

}

void sort_based_off_artist_name(Node **list, int nummSongs) {
	Node *front = NULL, *back = NULL;
	int imaxmSongs = (mNumOfSongs - 1);
	int  jmaxmSongs = (mNumOfSongs - 1);
	if ((*list != NULL) && ((*list)->mNext != NULL)) {
		front = *list;
		back = (*list)->mNext;
		for (int i = 0; i < imaxmSongs; i++) {
			for (int j = 0; j < jmaxmSongs; j++) {
				if (strcmp(front->mmSong.mArtist, back->mmSong.mArtist) > 0) {
					Node *tempf = front->mPrevious, *tempb = back->mNext, *temp = back;
					front = back;
					back = back->mPrevious;
					if (tempf != NULL) {
						tempf->mNext = front;
					}
					else {
						*list = front;
					}
					if (tempb != NULL) {
						tempb->mPrevious = back;
					}
					front->mNext = back;
					front->mPrevious = tempf;
					back->mPrevious = front;
					back->mNext = tempb;
				}
				Node *temp = back;
				back = back->mNext;
				front = temp;
			}
			jmaxmSongs--;
			front = *list;
			back = (*list)->mNext;
		}
	}
}

int * shuffle_all_array(int nummSongs) {
	int *shuffle_all = NULL;
	shuffle_all = (int)malloc((sizeof(int)*nummSongs));
	for (int i = 0; i < nummSongs; i++) {
		shuffle_all[i] = i;
	}
	for (int j = 0; j < nummSongs; j++) {
		int index = shuffle_all[j];
		int random = rand() % nummSongs;

		shuffle_all[j] = shuffle_all[random];
		shuffle_all[random] = index;
	}
	return shuffle_all;
}

void shuffle_all(Node * list) {
	int * tempshuffle_all = NULL;
	tempshuffle_all = shuffle_all_array(mNumOfSongs);
	display_shuffle_all(tempshuffle_all, list);
}

void display_shuffle_all(int shuffle_all[], Node * list) {
	int index = 0, currI = 0, nextI = 0, position = 0;

	Node *tempNode = list;
	nextI = shuffle_all[position];

	do {
		printf("Playing: \n");

		if (currI < nextI) {
			for (int i = currI; i < nextI; i++) {
				tempNode = tempNode->mNext;
			}
		}
		else {
			for (int i = currI; i > nextI; i--) {
				tempNode = tempNode->mPrevious;
			}
		}
		printf(" %s, %s,%s,%s,%d:%d,%d,%d \n", tempNode->mmSong.mArtist, tempNode->mmSong.mAlbum, tempNode->mmSong.mSong, tempNode->mmSong.mGenre, tempNode->mmSong.mTime.mMin, tempNode->mmSong.mTime.mSec, tempNode->mmSong.mNumberOfTimesPlayed, tempNode->mmSong.mRating);
		system("pause");
		system("cls");

		index++;
		position++;
		tempNode->mmSong.mNumberOfTimesPlayed++;

		if (index < mNumOfSongs) {
			currI = nextI;
			nextI = shuffle_all[position];
		}
	} while (index < mNumOfSongs);
}

void sort_based_off_album(Node **list, int nummSongs) {
	Node *front = NULL, *back = NULL;
	int imaxmSongs = (mNumOfSongs - 1);
	int  jmaxmSongs = (mNumOfSongs - 1);
	if ((*list != NULL) && ((*list)->mNext != NULL)) {
		front = *list;
		back = (*list)->mNext;
		for (int i = 0; i < imaxmSongs; i++) {
			for (int j = 0; j < jmaxmSongs; j++) {
				if (strcmp(front->mmSong.mAlbum, back->mmSong.mAlbum) > 0) {
					Node *tempf = front->mPrevious, *tempb = back->mNext, *temp = back;
					front = back;
					back = back->mPrevious;
					if (tempf != NULL) {
						tempf->mNext = front;
					}
					else {
						*list = front;
					}
					if (tempb != NULL) {
						tempb->mPrevious = back;
					}
					front->mNext = back;
					front->mPrevious = tempf;
					back->mPrevious = front;
					back->mNext = tempb;
				}
				Node *temp = back;
				back = back->mNext;
				front = temp;
			}
			jmaxmSongs--;
			front = *list;
			back = (*list)->mNext;
		}
	}
}


void sort_based_of_rating(Node **list, int nummSongs) {
	Node *front = NULL, *back = NULL;
	int imaxmSongs = (mNumOfSongs - 1);
	int  jmaxmSongs = (mNumOfSongs - 1);
	if ((*list != NULL) && ((*list)->mNext != NULL)) {
		front = *list;
		back = (*list)->mNext;
		for (int i = 0; i < imaxmSongs; i++) {
			for (int j = 0; j < jmaxmSongs; j++) {
				if (front->mmSong.mRating < back->mmSong.mRating) {
					Node *tempf = front->mPrevious, *tempb = back->mNext, *temp = back;
					front = back;
					back = back->mPrevious;
					if (tempf != NULL) {
						tempf->mNext = front;
					}
					else {
						*list = front;
					}
					if (tempb != NULL) {
						tempb->mPrevious = back;
					}
					front->mNext = back;
					front->mPrevious = tempf;
					back->mPrevious = front;
					back->mNext = tempb;
				}
				Node *temp = back;
				back = back->mNext;
				front = temp;
			}
			jmaxmSongs--;
			front = *list;
			back = (*list)->mNext;
		}
	}
}

void sort_based_off_number_of_times_played(Node **list, int nummSongs) {
	Node *front = NULL, *back = NULL;
	int imaxmSongs = (mNumOfSongs - 1);
	int  jmaxmSongs = (mNumOfSongs - 1);
	if ((*list != NULL) && ((*list)->mNext != NULL)) {
		front = *list;
		back = (*list)->mNext;
		for (int i = 0; i < imaxmSongs; i++) {
			for (int j = 0; j < jmaxmSongs; j++) {
				if (front->mmSong.mNumberOfTimesPlayed < back->mmSong.mNumberOfTimesPlayed) {
					Node *tempf = front->mPrevious, *tempb = back->mNext, *temp = back;
					front = back;
					back = back->mPrevious;
					if (tempf != NULL) {
						tempf->mNext = front;
					}
					else {
						*list = front;
					}
					if (tempb != NULL) {
						tempb->mPrevious = back;
					}
					front->mNext = back;
					front->mPrevious = tempf;
					back->mPrevious = front;
					back->mNext = tempb;
				}
				Node *temp = back;
				back = back->mNext;
				front = temp;
			}
			jmaxmSongs--;
			front = *list;
			back = (*list)->mNext;
		}
	}
}