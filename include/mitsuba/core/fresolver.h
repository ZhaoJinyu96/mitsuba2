#pragma once

#include <mitsuba/core/filesystem.h>
#include <mitsuba/core/object.h>
#include <iosfwd>

NAMESPACE_BEGIN(mitsuba)

/**
 * \brief Simple class for resolving paths on Linux/Windows/Mac OS
 *
 * This convenience class looks for a file or directory given its name
 * and a set of search paths. The implementation walks through the
 * search paths in order and stops once the file is found.
 */
class MTS_EXPORT_CORE FileResolver : public Object {
public:
    typedef std::vector<fs::path>::iterator iterator;
    typedef std::vector<fs::path>::const_iterator const_iterator;

    /// Initialize a new file resolver with the current working directory
    FileResolver();

    /// Walk through the list of search paths and try to resolve the input path
    fs::path resolve(const fs::path &path) const;

    /// Return the number of search paths
    size_t size() const { return m_paths.size(); }

    /// Return an iterator at the beginning of the list of search paths
    iterator begin() { return m_paths.begin(); }

    /// Return an iterator at the end of the list of search paths
    iterator end()   { return m_paths.end(); }

    /// Return an iterator at the beginning of the list of search paths (const)
    const_iterator begin() const { return m_paths.begin(); }

    /// Return an iterator at the end of the list of search paths (const)
    const_iterator end()   const { return m_paths.end(); }

    /// Erase the entry at the given iterator position
    void erase(iterator it) { m_paths.erase(it); }

    /// Erase the search path from the list
    void erase(const fs::path &p) {
        m_paths.erase(std::remove(m_paths.begin(), m_paths.end(), p), m_paths.end());
    }

    /// Clear the list of search paths
    void clear() { m_paths.clear(); }

    /// Prepend an entry at the beginning of the list of search paths
    void prepend(const fs::path &path) { m_paths.insert(m_paths.begin(), path); }

    /// Append an entry to the end of the list of search paths
    void append(const fs::path &path) { m_paths.push_back(path); }

    /// Return an entry from the list of search paths
    fs::path &operator[](size_t index) { return m_paths[index]; }

    /// Return an entry from the list of search paths (const)
    const fs::path &operator[](size_t index) const { return m_paths[index]; }

    /// Print a human-readable representation of this instance
    friend MTS_EXPORT_CORE std::ostream &operator<<(std::ostream &os, const FileResolver &r);

    MTS_DECLARE_CLASS()
private:
    std::vector<fs::path> m_paths;
};

NAMESPACE_END(mitsuba)
