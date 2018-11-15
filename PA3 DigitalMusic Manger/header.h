/*
* Desta Pickering
* Created: September 2017
* Updated: November 2018
* Descriptioin: This program will simulate many of the instances of a basic music player... It takes a file filled with mSongs
*					and creates a link list
*/


// Gaurd Code
#ifndef MUSIC_PLAYLIST_SIMULATOR_H
#define MUSIC_PLAYLIST_SIMULATOR_H

// Necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct duration{
	int mMin;
	int mSec;
}Duration;

typedef struct record{
	char mArtist[100];
	char mAlbum[100];
	char mSong[100];
	char mGenre[100];
	Duration mTime;
	int mNumberOfTimesPlayed;
	int mRating;
}Record;

typedef struct node{
	Record mmSong;
	struct node * mPrevious;
	struct node * mNext;
}Node;

// Member of the songs in musicPlayList.csv
int mNumOfSongs;

// @see fill_record()
Node *fill_record(Record songInformation);

// @see import_line()
Record import_line(char line[]);

// @see import_length()
Duration import_length(char * length);

// @see insert_at_front()
void insert_at_front(Node **rList, Record songInformation);

// @see store_song()
void store_song(Node *rList, FILE *output);

// @see displaySongs()
void display_by_song(Node *rList);

// @see displayByArtist()
void display_by_artist(Node *rList, char *mArtistName);

// @see editSongByArtist
void edit_song_by_artist_name(Node **rList, char * mArtistName);

// @see edit_rating_by_artist_name()
void edit_rating_by_artist_name(Node **rList, char *mArtistName);

// @see play_all_songs()
void play_all_songs(Node *rList);

// @see add_record()
void add_record(Node **rList);

// @see remove_song_from_list()
void remove_song_from_list(Node**rList, char *mSongTitle);

// @see sort_menu()
void sort_menu(Node **rList);

// @see sort_based_off_artist_name()
void sort_based_off_artist_name(Node **rList, int nummSongs);

// @see sort_based_off_album()
void sort_based_off_album(Node**rList, int nummSongs);

// @see sort_based_of_rating()
void sort_based_of_rating(Node **rList, int nummSongs);

// @see sort_based_off_number_of_times_played()
void sort_based_off_number_of_times_played(Node ** rList, int mNumOfSongs);

// @see shuffle_all_array()
int * shuffle_all_array(int nummSongs);

// @see shuffle_all_all()
void shuffle_all(Node *rList);

// @see display_shuffle_all()
void display_shuffle_all(int random[], Node *rList);

#endif //MUSIC_PLAYLIST_SIMULATOR_H