#include "header.h"

int main() {
	FILE* infile = NULL, *outfile = NULL;
	char line[100] = "", copyLine[100] = "", mArtistName[100] = "";
	char mSongTitle[100];
	Node * head = NULL;
	int option = 0;

	infile = fopen("musicPlayList.csv", "r");

	if (infile != NULL) {
		do {
			do {
				//option = 0;
				system("cls");
				printf("Welcome to you music play list! \n");
				printf("Please choose which option you would like: \n");
				printf("(1) load \n");
				printf("(2) store \n");
				printf("(3) display \n");
				printf("(4) insert \n");
				printf("(5) delete \n");
				printf("(6) edit \n");
				printf("(7) sort \n");
				printf("(8) rate \n");
				printf("(9) play \n");
				printf("(10) shuffle_all \n");
				printf("(11) exit \n");
				scanf(" %d", &option);
			} while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != 9 && option != 10 && option != 11); // end of the menu while loop
			if (option == 1) {
				Record temp;
				while (!feof(infile)) {
					fgets(line, 100, infile);
					strcpy(copyLine, line);
					temp = import_line(copyLine);
					insert_at_front(&head, temp);
				}
				fclose(infile);

				printf("Complete!");

				system("pause");
				system("cls");
			}

			if (option == 2) {
				infile = fopen("store.csv", "w");
				store_song(head, infile);
				fclose(infile);
			}
			if (option == 3) {

				do {
					printf("Please choose what you would like to display. \n");
					printf(" \t (1) Print all records. \n");
					printf(" \t (2) Print all records that match an mArtist\n");
					scanf("%d", &option);
				} while (option != 1 && option != 2); // end of display menu
				if (option == 1) {
					system("cls");
					display_by_song(head);
					system("pause");
				}
				if (option == 2) {
					printf("Enter the name of the mArtist: ");
					scanf(" %[^\n]s", &mArtistName);
					display_by_artist(head, mArtistName);
					system("pause");
				}
				system("cls");
			}
			if (option == 4) {
				system("cls");
				add_record(&head);
				system("pause");
				display_by_song(head);
				system("pause");
				system("cls");
			}

			if (option == 5) {
				system("cls");
				printf("What mSong would you like to delete?\n");
				scanf(" %[^\n]s", mSongTitle);
				system("cls");
				remove_song_from_list(&head, mSongTitle);
				display_by_song(head);
				system("pause");
			}
			if (option == 6) {
				system("cls");
				printf("What is the name of the mArtist whose mSong you wish to edit. \n");
				scanf(" %[^\n]s", &mArtistName);
				system("cls");
				edit_song_by_artist_name(&head, mArtistName);
				system("pause");
			}
			if (option == 7) {

				system("cls");
				sort_menu(&head);
			}
			if (option == 8) {
				system("cls");
				printf("What is the name of the arist whose mSong's mRating you would like to change? \n");
				scanf(" %[^\n]s", &mArtistName);
				system("cls");
				edit_rating_by_artist_name(&head, mArtistName);
				system("pause");
			}

			if (option == 9) {
				system("cls");
				play_all_songs(head);
				system("pause");
			}//end of if statement for play
			if (option == 10) {
				system("cls");
				shuffle_all(head);
				system("pause");
			}// end of if statement for shuffle_all
			if (option == 11) {
				infile = fopen("store", "w");
				store_song(head, infile);
				fclose(infile);
			}
		} while (option != 11); // end of the outter while loop
	}
	return 0;
}