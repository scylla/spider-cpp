#include <vector>
#include <utility>
#include "download_manager.hpp"

spider::DownloadManager::DownloadManager(ThreadPool & pool, UrlTracker & tracker)
    : m_pool(pool), m_tracker(tracker) {
}

void spider::DownloadManager::associate(
    Categorizer const& categorizer, 
    DownloadFactory const& factory) {
    m_categories.push_back(std::pair<Categorizer const&, DownloadFactory const&>(categorizer, factory));
}
