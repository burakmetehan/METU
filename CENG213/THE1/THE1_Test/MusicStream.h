#ifndef MUSICSTREAMINGSERVICE_H
#define MUSICSTREAMINGSERVICE_H

#include "LinkedList.h"
#include "Album.h"
#include "Artist.h"
#include "Profile.h"
#include "Song.h"

class MusicStream {
public: // DO NOT CHANGE THIS PART.
    MusicStream() {}

    void addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan);
    void deleteProfile(const std::string &email);

    void addArtist(const std::string &artistName);
    void addAlbum(const std::string &albumName, int artistId);
    void addSong(const std::string &songName, int songDuration, int albumId);

    void followProfile(const std::string &email1, const std::string &email2);
    void unfollowProfile(const std::string &email1, const std::string &email2);

    void createPlaylist(const std::string &email, const std::string &playlistName);
    void deletePlaylist(const std::string &email, int playlistId);
    void addSongToPlaylist(const std::string &email, int songId, int playlistId);
    void deleteSongFromPlaylist(const std::string &email, int songId, int playlistId);
    LinkedList<Song *> playPlaylist(const std::string &email, Playlist *playlist);
    Playlist *getPlaylist(const std::string &email, int playlistId);
    LinkedList<Playlist *> getSharedPlaylists(const std::string &email);
    void shufflePlaylist(const std::string &email, int playlistId, int seed);
    void sharePlaylist(const std::string &email, int playlistId);
    void unsharePlaylist(const std::string &email, int playlistId);

    void subscribePremium(const std::string &email);
    void unsubscribePremium(const std::string &email);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    Node<Profile> *find_profile_by_email(const std::string &email) {
        Node<Profile> *temp = profiles.getFirstNode();
        
        if (temp)
        {
            do
            {
                if (temp->data.getEmail() == email)
                {
                    break;
                }

                temp = temp->next;
            } while (temp != profiles.getFirstNode());
        }
        else;
        
        return temp;
    }

    Node<Artist> *find_artist_by_id(int artistId) {
        Node<Artist> *temp = artists.getFirstNode();

        if (temp)
        {
            do
            {
                if (temp->data.getArtistId() == artistId)
                {
                    break;
                }

                temp = temp->next;
            } while (temp != artists.getFirstNode());
        }
        else;
        
        return temp;
    }

    Node<Album> *find_album_by_id(int albumId) {
        Node<Album> *temp = albums.getFirstNode();

        if (temp)
        {
            do
            {
                if (temp->data.getAlbumId() == albumId)
                {
                    break;
                }

                temp = temp->next;
            } while (temp != albums.getFirstNode());
        }
        else;
        
        return temp;
    }

    Node<Song> *find_song_by_id(int songId) {
        Node<Song> *temp = songs.getFirstNode();

        if (temp)
        {
            do
            {
                if (temp->data.getSongId() == songId)
                {
                    break;
                }

                temp = temp->next;            
            } while (temp != songs.getFirstNode());
        }

        return temp;
    }

    Node<Playlist> *find_playlist_by_id(Node<Profile> *user, int playlistId) {
        Node<Playlist> *temp = user->data.getPlaylists().getFirstNode();

        if (temp)
        {
            do
            {
                if (temp->data.getPlaylistId() == playlistId)
                {
                    break;
                }

                temp = temp->next;
            } while (temp != user->data.getPlaylists().getFirstNode());
        }
        else;
        
        return temp;
    }

private: // DO NOT CHANGE THIS PART.
    LinkedList<Profile> profiles;
    LinkedList<Artist> artists;
    LinkedList<Album> albums;
    LinkedList<Song> songs;
};

#endif //MUSICSTREAMINGSERVICE_H
