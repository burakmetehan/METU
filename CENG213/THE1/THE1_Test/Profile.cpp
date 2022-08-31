#include "Profile.h"

// My Helper Function
Node<Playlist> *find_playlist_by_id(LinkedList<Playlist> &playlists, int playlistId) {
    if (playlists.getFirstNode())
    {
        Node<Playlist> *playlist_ptr = playlists.getFirstNode();
        do
        {
            if (playlist_ptr->data.getPlaylistId() == playlistId)
            {
                break;
            }
            
            playlist_ptr = playlist_ptr->next;
        } while (playlist_ptr != playlists.getFirstNode());
        return playlist_ptr;
    }
    else 
        return NULL;
}

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    following.insertAtTheEnd(profile);
    profile->getFollowers().insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile) {
    following.removeNode(profile);
    profile->getFollowers().removeNode(this);
}

void Profile::createPlaylist(const std::string &playlistName) {
    playlists.insertAtTheEnd(Playlist(playlistName));
}

void Profile::deletePlaylist(int playlistId) {
    playlists.removeNode(find_playlist_by_id(playlists, playlistId));
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    find_playlist_by_id(playlists, playlistId)->data.addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    find_playlist_by_id(playlists, playlistId)->data.dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) {
    return &(find_playlist_by_id(playlists, playlistId)->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    Node<Profile *> *user_friend = following.getFirstNode();
    LinkedList<Playlist *> shared_list;

    if (user_friend)
    {
        do
        {
            Node<Playlist> *new_list_ptr = user_friend->data->getPlaylists().getFirstNode();

            if (new_list_ptr)
            {
                do
                {
                    if (new_list_ptr->data.isShared())
                    {
                        shared_list.insertAtTheEnd(&(new_list_ptr->data));
                    }

                    new_list_ptr = new_list_ptr->next;
                } while (new_list_ptr != user_friend->data->getPlaylists().getFirstNode());
            }
            else;

            user_friend = user_friend->next;
        } while (user_friend != following.getFirstNode());
    }
    else;

    return shared_list;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    find_playlist_by_id(playlists, playlistId)->data.shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    find_playlist_by_id(playlists, playlistId)->data.setShared(true);
}

void Profile::unsharePlaylist(int playlistId) {
    find_playlist_by_id(playlists, playlistId)->data.setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
