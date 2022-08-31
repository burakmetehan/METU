#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    profiles.insertAtTheEnd(Profile(email, username, plan));
}

void MusicStream::deleteProfile(const std::string &email) {
    Node<Profile> *user = find_profile_by_email(email);

    // Deleting the user from its followers' list of followings
    if (!(user->data.getFollowings().isEmpty()))
    {
        Node<Profile *> *followings_current = user->data.getFollowings().getFirstNode();

        do
        {
            LinkedList<Profile *> *followers = &(followings_current->data->getFollowers());
            Node<Profile *> *followers_current = followers->getFirstNode();
            
            do
            {
                if (*(followers_current->data) == user->data)
                {
                    followers->removeNode(followers_current); 
                    break; 
                }

                followers_current = followers_current->next;
            } while (followers_current != followers_current->data->getFollowers().getFirstNode());

            followings_current = followings_current->next;
        } while (followings_current != user->data.getFollowings().getFirstNode());
        
    }
    else;

    // Deleting the user from its followings' list of followers
    if (!(user->data.getFollowers().isEmpty()))
    {
        Node<Profile *> *followers_current = user->data.getFollowers().getFirstNode();

        do
        {
            LinkedList<Profile *> *followings = &(followers_current->data->getFollowings());
            Node<Profile *> *followings_current = followings->getFirstNode();

            do
            {
                if (*(followings_current->data) == user->data)
                {
                    followings->removeNode(followings_current);
                    break;
                }

                followings_current = followings_current->next;
            } while (followings_current != followings_current->data->getFollowings().getFirstNode());

            followers_current = followers_current->next;        
        } while (followers_current != user->data.getFollowers().getFirstNode());
    }

    // Deleting Profile's content
    user->data.getPlaylists().~LinkedList();
    user->data.getFollowings().~LinkedList();
    user->data.getFollowers().~LinkedList();
    profiles.removeNode(user);
}

void MusicStream::addArtist(const std::string &artistName) {
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    // Adding album to albums
    albums.insertAtTheEnd(Album(albumName));
    //Adding album to artist
    find_artist_by_id(artistId)->data.addAlbum(&(albums.getLastNode()->data));
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    // Adding song to songs
    songs.insertAtTheEnd(Song(songName, songDuration));
    // Adding song to album
    find_album_by_id(albumId)->data.addSong(&(songs.getLastNode()->data));
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> 
        *user1 = find_profile_by_email(email1), 
        *user2 = find_profile_by_email(email2);
    
    user1->data.followProfile(&(user2->data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> 
        *user1 = find_profile_by_email(email1), 
        *user2 = find_profile_by_email(email2);
    
    user1->data.unfollowProfile(&(user2->data));
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    Node<Song> *song = find_song_by_id(songId);
    
    user->data.addSongToPlaylist(&(song->data), playlistId);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    Node<Song> *song = find_song_by_id(songId);

    user->data.deleteSongFromPlaylist(&(song->data), playlistId);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Node<Profile> *user = find_profile_by_email(email);

    if (user->data.getPlan() == premium)
    {
        LinkedList<Song *> new_list;
        new_list = playlist->getSongs();
        return new_list;
    }
    else
    {
        LinkedList<Song *> new_list = playlist->getSongs();
        new_list.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
        return new_list;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    Node<Playlist> *playlist = find_playlist_by_id(user, playlistId);
    
    return &(playlist->data);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {    
    Node<Profile> *user = find_profile_by_email(email);

    return user->data.getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.shufflePlaylist(playlistId, seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    Node<Profile> *user = find_profile_by_email(email);
    user->data.setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
