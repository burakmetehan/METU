#include <iostream>

#include "MusicStream.h"

using namespace std;

 
void test_album(){
    Album album("album1");
    cout << album << endl;

    Song *song_1 = new Song("Song1", 240);
    Song *song_2 = new Song("Song2", 360);
 
    album.addSong(song_1);
    cout << album << endl;

    album.addSong(song_2);
    cout << album << endl;

    album.dropSong(song_1);
    cout << album << endl;
}
/*
void test_artist(){
    Artist artist("artist1");
    
    Song *song_1 = new Song("Song 1", 240);
    Song *song_2 = new Song("Song 2", 360);
    Song *song_3 = new Song("Song 3", 150);
    Song *song_4 = new Song("Song 4", 450);
    Song *song_5 = new Song("Song 5", 90);
    
    Album *album_1 = new Album("Album 1");
    Album *album_2 = new Album("Album 2");

    cout << artist << endl;

    artist.addAlbum(album_1);
    cout << artist << endl;

    artist.addAlbum(album_2);
    cout << artist << endl;

    album_1->addSong(song_1);
    album_1->addSong(song_2);

    album_2->addSong(song_1);
    album_2->addSong(song_5);
    album_2->addSong(song_3);

    cout << artist << endl << endl;

    artist.dropAlbum(album_1);
    cout << artist << endl << endl;

    artist.dropAlbum(album_2);
    cout << artist << endl << endl;
}

void test_playlist() {
    Playlist playlist("Playlist 1");

    Song *song_1 = new Song("Song 1", 240);
    Song *song_2 = new Song("Song 2", 360);
    Song *song_3 = new Song("Song 3", 150);
    Song *song_4 = new Song("Song 4", 450);
    Song *song_5 = new Song("Song 5", 90);

    cout << playlist << endl << endl;

    playlist.addSong(song_1);
    playlist.addSong(song_2);
    playlist.addSong(song_3);
    playlist.addSong(song_4);
    playlist.addSong(song_5);

    cout << playlist << endl << endl;

    playlist.dropSong(song_1);
    playlist.dropSong(song_5);
    playlist.dropSong(song_3);

    cout << playlist << endl << endl;

    playlist.dropSong(song_2);
    playlist.dropSong(song_4);

    cout << playlist << endl << endl;

    playlist.addSong(song_1);
    playlist.addSong(song_2);
    playlist.addSong(song_3);
    playlist.addSong(song_4);
    playlist.addSong(song_5);

    cout << playlist << endl << endl;

    playlist.shuffle(31);

    cout << playlist << endl << endl;        
}

void test_profile() {
    Profile *profile_1 = new Profile("burak@gmail.com", "Burak", premium);
    Profile *profile_2 = new Profile("berfinnur@gmail.com", "Berfinnur", premium);
    Profile *profile_3 = new Profile("yusuf@gmail.com", "Yusuf", premium);
    Profile *profile_4 = new Profile("ersel@gmail.com", "Ersel", free_of_charge);
    Profile *profile_5 = new Profile("emre@gmail.com", "Emre", free_of_charge);
    Profile *profile_6 = new Profile("abbas@gmail.com", "Abbas", free_of_charge);

    Profile* profiles[6] = {profile_1, profile_2, profile_3, profile_4, profile_5, profile_6};

    Song *song_1 = new Song("Song 1", 240);
    Song *song_2 = new Song("Song 2", 360);
    Song *song_3 = new Song("Song 3", 150);
    Song *song_4 = new Song("Song 4", 450);
    Song *song_5 = new Song("Song 5", 90);

    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->followProfile(profile_2);
    profile_2->followProfile(profile_1);
    profile_1->followProfile(profile_3);
    profile_1->followProfile(profile_6);

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->unfollowProfile(profile_6);
    profile_1->unfollowProfile(profile_3);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->unfollowProfile(profile_2);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }
    
    profile_1->createPlaylist("Playlist 1");
    profile_1->createPlaylist("Playlist 2");
    profile_3->createPlaylist("Playlist 3");
    profile_1->createPlaylist("Playlist 4");
    //profile_4->createPlaylist("Playlist 5");
    //profile_5->createPlaylist("Playlist 6");
    //profile_1->createPlaylist("Playlist 7");

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->deletePlaylist(4);
    //profile_1->deletePlaylist(7);
    //profile_4->deletePlaylist(5);
    //profile_5->deletePlaylist(6);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->addSongToPlaylist(song_1, 1);
    profile_1->addSongToPlaylist(song_5, 2);
    profile_1->addSongToPlaylist(song_3, 1);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }


    profile_1->deleteSongFromPlaylist(song_1, 1);
    profile_1->deleteSongFromPlaylist(song_3, 1);
    profile_1->deleteSongFromPlaylist(song_5, 2);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->addSongToPlaylist(song_1, 1);
    profile_1->addSongToPlaylist(song_5, 2);
    profile_1->addSongToPlaylist(song_3, 1);

    Playlist *playlist_ptr = profile_1->getPlaylist(1);
    cout << playlist_ptr->getName() << endl;
    cout << playlist_ptr->getPlaylistId() << endl;
    playlist_ptr->getSongs().print();
    cout << song_1 << endl << song_3 << endl;

    playlist_ptr = profile_1->getPlaylist(2);
    cout << playlist_ptr->getName() << endl;
    cout << playlist_ptr->getPlaylistId() << endl;
    playlist_ptr->getSongs().print();
    cout << song_5 << endl;

    // Testşng getShared Playlist
    profile_1->getPlaylist(1)->setShared(true);
    cout << profile_1->getSharedPlaylists().getFirstNode()->data->getName() << endl;

    // Testing shufflePlayList
    cout << "Testing shufflePlayList" << endl;
    profile_1->addSongToPlaylist(song_5, 1);
    profile_1->addSongToPlaylist(song_2, 1);
    profile_1->addSongToPlaylist(song_4, 1);

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->shufflePlaylist(1, 31);

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->deleteSongFromPlaylist(song_1, 1);
    profile_1->deleteSongFromPlaylist(song_2, 1);
    profile_1->deleteSongFromPlaylist(song_3, 1);
    profile_1->deleteSongFromPlaylist(song_4, 1);
    profile_1->deleteSongFromPlaylist(song_5, 1);

    // Testing sharePlaylist
    cout << "Testing sharePlaylist" << endl;

    profile_1->getPlaylist(1)->setShared(false);
    profile_1->getPlaylist(2)->setShared(false);
    profile_2->createPlaylist("Playlist 3");
    profile_1->createPlaylist("Playlist 4");
    profile_1->getPlaylist(4)->setShared(false);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 1; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->sharePlaylist(1);
    profile_1->sharePlaylist(2);
    profile_1->sharePlaylist(6);

    cout << "--------------------------\n";
    for (int i = 0; i < 1; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    // Testing unsharePlaylist
    cout << "Testing unsharePlaylist" << endl;

    profile_1->getPlaylist(1)->setShared(true);
    profile_1->getPlaylist(2)->setShared(true);
    profile_1->getPlaylist(6)->setShared(true);
    
    cout << "--------------------------\n";
    for (int i = 0; i < 1; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->unsharePlaylist(1);
    profile_1->unsharePlaylist(2);
    profile_1->unsharePlaylist(6);

    cout << "--------------------------\n";
    for (int i = 0; i < 1; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }
}

void test_profile() {
    Profile *profile_1 = new Profile("burak@gmail.com", "Burak", premium);
    Profile *profile_2 = new Profile("berfinnur@gmail.com", "Berfinnur", premium);
    Profile *profile_3 = new Profile("yusuf@gmail.com", "Yusuf", premium);
    Profile *profile_4 = new Profile("ersel@gmail.com", "Ersel", free_of_charge);
    Profile *profile_5 = new Profile("emre@gmail.com", "Emre", free_of_charge);
    Profile *profile_6 = new Profile("abbas@gmail.com", "Abbas", free_of_charge);

    Profile* profiles[6] = {profile_1, profile_2, profile_3, profile_4, profile_5, profile_6};

    Song *song_1 = new Song("Song 1", 240);
    Song *song_2 = new Song("Song 2", 360);
    Song *song_3 = new Song("Song 3", 150);
    Song *song_4 = new Song("Song 4", 450);
    Song *song_5 = new Song("Song 5", 90);

    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->followProfile(profile_2);
    profile_2->followProfile(profile_1);
    profile_1->followProfile(profile_3);
    profile_1->followProfile(profile_6);

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }

    profile_1->unfollowProfile(profile_2);

    cout << "--------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << *(profiles[i]) << endl << endl;
    }
}

void test_musicstream() {
    MusicStream ms;
    ms.print();

    // Testing addProfile
    cout << "===============\nTesting addProfile\n===============" << endl;

    ms.addProfile("burak@metu.edu.tr", "burak", premium);
    ms.addProfile("berfinnur@metu.edu.tr", "berfinnur", premium);
    ms.addProfile("abbas@metu.edu.tr", "abbas", premium);
    ms.print();

    // Testing deleteProfile
    cout << "===============\nTesting deleteProfile\n===============" << endl;

    cout << "Before Deletion:" << endl;
    ms.followProfile("burak@metu.edu.tr", "berfinnur@metu.edu.tr");
    ms.followProfile("burak@metu.edu.tr", "abbas@metu.edu.tr");
    ms.followProfile("berfinnur@metu.edu.tr", "burak@metu.edu.tr");
    ms.followProfile("berfinnur@metu.edu.tr", "abbas@metu.edu.tr");
    ms.followProfile("abbas@metu.edu.tr", "burak@metu.edu.tr");
    ms.followProfile("abbas@metu.edu.tr", "berfinnur@metu.edu.tr");
    ms.print();

    cout << "After Deletion:" << endl;
    ms.deleteProfile("abbas@metu.edu.tr");
    ms.print();

    // Testing addArtist
    cout << "===============\nTesting addArtist\n===============" << endl;

    ms.addArtist("Artist 1");
    ms.addArtist("Artist 2");
    ms.addArtist("Artist 3");
    ms.print();

    // Testing addAlbum
    cout << "===============\nTesting addAlbum\n===============" << endl;

    ms.addAlbum("Album 1", 3);
    ms.addAlbum("Album 2", 1);
    ms.addAlbum("Album 3", 2);
    
    ms.print();

    // Testing addSong
    cout << "===============\nTesting addSong\n===============" << endl;

    ms.addSong("Song 1", 150, 1);
    ms.addSong("Song 2", 180, 2);
    ms.addSong("Song 3", 210, 3);
    ms.addSong("Song 4", 240, 1);
    ms.addSong("Song 5", 270, 2);
    ms.addSong("Song 6", 300, 3);
    ms.print();

    // Testing followProfile
    cout << "===============\nTesting followProfile\n===============" << endl;

    ms.followProfile("burak@metu.edu.tr", "berfinnur@metu.edu.tr");
    ms.followProfile("burak@metu.edu.tr", "abbas@metu.edu.tr");
    ms.followProfile("berfinnur@metu.edu.tr", "burak@metu.edu.tr");
    ms.print();

    // Testing unfollowProfile
    cout << "===============\nTesting unfollowProfile\n===============" << endl;

    ms.unfollowProfile("burak@metu.edu.tr", "berfinnur@metu.edu.tr");
    ms.unfollowProfile("burak@metu.edu.tr", "abbas@metu.edu.tr");
    ms.unfollowProfile("berfinnur@metu.edu.tr", "burak@metu.edu.tr");
    ms.print();
    
    // Testing createPlaylist
    cout << "===============\nTesting createPlaylist\n===============" << endl;

    ms.createPlaylist("burak@metu.edu.tr", "Playlist 1");
    ms.createPlaylist("abbas@metu.edu.tr", "Playlist 2");
    ms.print();

    // Testing deletePlaylist
    cout << "===============\nTesting deletePlaylist\n===============" << endl;

    ms.createPlaylist("burak@metu.edu.tr", "Playlist 3");
    ms.print();

    ms.deletePlaylist("burak@metu.edu.tr", 3);
    ms.print();

    ms.deletePlaylist("burak@metu.edu.tr", 1);
    ms.print();

    // Testing addSongToPlaylist
    cout << "===============\nTesting addSongToPlaylist\n===============" << endl;

    ms.createPlaylist("burak@metu.edu.tr", "My_List");
    ms.addSongToPlaylist("burak@metu.edu.tr", 3, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 5, 4);
    ms.addSongToPlaylist("abbas@metu.edu.tr", 4, 2);
    ms.print();

    // Testing deleteSongToPlaylist
    cout << "===============\nTesting deleteSongToPlaylist\n===============" << endl;

    ms.deleteSongFromPlaylist("burak@metu.edu.tr", 3, 4);
    ms.deleteSongFromPlaylist("abbas@metu.edu.tr", 4, 2);
    ms.deleteSongFromPlaylist("brak@metu.edu.tr", 5, 4);
    ms.print();


    // Testing playPlaylist
    cout << "===============\nTesting playPlaylist\n===============" << endl;

    
    ms.addSongToPlaylist("burak@metu.edu.tr", 3, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 5, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 1, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 4, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 7, 4);

    LinkedList<Song *> test_songs = ms.getPlaylist("burak@metu.edu.tr", 4)->getSongs();
    for (int i = 0; i < test_songs.getSize(); i++)
    {
        cout << *(test_songs.getNodeAtIndex(i)->data) << endl;
    }

    
    cout << "Premium:" << endl;    
    Playlist *temp = ms.getPlaylist("burak@metu.edu.tr", 4);
    LinkedList<Song *> test = ms.playPlaylist("burak@metu.edu.tr", temp);
    //test.print();
    for (int i = 0; i < test.getSize(); i++)
    {
        cout << *test.getNodeAtIndex(i)->data << endl;
    }

    cout << "free_of_charge:\n";
    ms.unsubscribePremium("burak@metu.edu.tr");
    temp = ms.getPlaylist("burak@metu.edu.tr", 4);
    test = ms.playPlaylist("burak@metu.edu.tr", temp);
    for (int i = 0; i < test.getSize(); i++)
    {
        cout << *test.getNodeAtIndex(i)->data << endl;
    }

    // Testing getPlaylist
    cout << "===============\nTesting getPlaylist\n===============" << endl;

    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << "\n";
    cout << *ms.getPlaylist("abbas@metu.edu.tr", 2) << "\n";

    // Testing sharePlaylist
    cout << "===============\nTesting sharePlaylist\n===============" << endl;

    ms.createPlaylist("burak@metu.edu.tr", "Playlist 8");
    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << "\n";
    cout << *ms.getPlaylist("burak@metu.edu.tr", 5) << "\n";
    
    ms.sharePlaylist("burak@metu.edu.tr", 4);
    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << "\n";

    // Testing getSharedPlaylists
    cout << "===============\nTesting getSharedPlaylists\n===============" << endl;
    
    cout << ms.getSharedPlaylists("burak@metu.edu.tr").getSize() << endl;
    cout << *(ms.getSharedPlaylists("burak@metu.edu.tr").getFirstNode()->data) << endl;
    
    // Testing unsharePlaylist
    cout << "===============\nTesting unsharePlaylist\n===============" << endl;

    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << "\n";
    ms.unsharePlaylist("burak@metu.edu.tr", 4);
    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << "\n";

    // Testing shufflePlaylist
    cout << "===============\nTesting shufflePlaylist\n===============" << endl;

    ms.addSongToPlaylist("burak@metu.edu.tr", 3, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 5, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 1, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 4, 4);
    ms.addSongToPlaylist("burak@metu.edu.tr", 7, 4);

    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << endl;
    ms.shufflePlaylist("burak@metu.edu.tr", 4, 31);
    cout << *ms.getPlaylist("burak@metu.edu.tr", 4) << endl;

    // Testing unsubscribePremium
    cout << "===============\nTesting unsubscribePremium\n===============" << endl;
    ms.print();
    ms.unsubscribePremium("burak@metu.edu.tr");
    ms.print();

    // Testing subscribePremium
    cout << "===============\nTesting subscribePremium\n===============" << endl;

    ms.subscribePremium("burak@metu.edu.tr");
    ms.print();

    // End of the testing
    cout << "===============\nEnd of the testing\n===============" << endl;
 }

void additional_test() {
    MusicStream ms;

    ms.addProfile("jack@sophia.com", "jack_sophia", free_of_charge);
    ms.addProfile("archie@rosie.com", "archie_rosie", premium);
    ms.addProfile("harry@isabella", "harry_isabella", free_of_charge);
    ms.addProfile("oscar@lily.com", "oscar_lily", premium);
    ms.addProfile("leo@lily.com", "leo_ivy", free_of_charge);

    ms.followProfile("jack@sophia.com", "harry@isabella");
    
    ms.followProfile("archie@rosie.com", "oscar@lily.com");
    ms.followProfile("oscar@lily.com", "archie@rosie.com");
    ms.followProfile("archie@rosie.com", "harry@isabella.com");
 
    ms.print();
 
    ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);

    ms.addSong("Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.createPlaylist("archie@rosie.com", "archie's favorites");
    ms.createPlaylist("oscar@lily.com", "oscar's goat");
    ms.createPlaylist("oscar@lily.com", "oscar's throwback playlist");

    ms.addSongToPlaylist("archie@rosie.com", 2, 1);
    ms.addSongToPlaylist("archie@rosie.com", 3, 1);
    ms.addSongToPlaylist("oscar@lily.com", 4, 2);
    ms.addSongToPlaylist("oscar@lily.com", 2, 3);
    ms.addSongToPlaylist("oscar@lily.com", 5, 3);

    ms.print();

    ms.sharePlaylist("archie@rosie.com", 1);
    ms.sharePlaylist("oscar@lily.com", 2);
    ms.sharePlaylist("oscar@lily.com", 3);

    ms.print();

    ms.unsharePlaylist("archie@rosie.com", 1);

    ms.print();

    cout << "getSharedPlaylists" << endl;
    LinkedList<Playlist *> test = ms.getSharedPlaylists("archie@rosie.com");
    for (int i=0; i < test.getSize(); i++)
    {
        cout << *test.getNodeAtIndex(i)->data << endl;
    }
}*/

int main() {
    //test_album();
    //test_artist();
    //test_playlist();
    //test_profile();
    //test_musicstream();
    //additional_test();

    return 0;
}

/*
int main() {
    MusicStream ms;

    ms.print();

    ms.addProfile("john@doe.com", "john_doe", free_of_charge);

    ms.print();

    ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);

    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.print();

    return 0;
}
*/