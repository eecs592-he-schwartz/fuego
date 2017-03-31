//----------------------------------------------------------------------------
/** @file FuegoMainUtil.cpp
    See FuegoMainUtil.h */
//----------------------------------------------------------------------------

#include "SgSystem.h"
#include "FuegoMainUtil.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include "GoBook.h"
#include "SgDebug.h"

using namespace std;
using namespace boost::filesystem;

//----------------------------------------------------------------------------

namespace {

bool LoadBookFile(GoBook& book, const path& file)
{
    path normalizedFile = file;
    normalizedFile.normalize();
    # if defined(BOOST_FILESYSTEM_VERSION)
       SG_ASSERT (BOOST_FILESYSTEM_VERSION == 2 || BOOST_FILESYSTEM_VERSION == 3);
    #endif

    #if (defined (BOOST_FILESYSTEM_VERSION) && (BOOST_FILESYSTEM_VERSION == 3))
        string nativeFile = normalizedFile.string();
    #else
        string nativeFile = normalizedFile.native_file_string();
    #endif	
    SgDebug() << "Loading opening book from '" << nativeFile << "'... ";
    std::ifstream in(nativeFile.c_str());
    if (! in)
    {
        SgDebug() << "not found\n";
        return false;
    }
    try
    {
        book.Read(in);
    }
    catch (const SgException& e)
    {
        SgDebug() << "error: " << e.what() << '\n';
        return false;
    }
    SgDebug() << "ok\n";
    return true;
}

} // namespace

//----------------------------------------------------------------------------

void FuegoMainUtil::LoadBook(GoBook& book,
                             const boost::filesystem::path& programDir)
{
    const string fileName = "book.dat";
    if (LoadBookFile(book, programDir / fileName))
        return;
#ifdef ABS_TOP_SRCDIR
    if (LoadBookFile(book, path(ABS_TOP_SRCDIR) / "book" / fileName))
        return;
#endif
#if defined(DATADIR) && defined(PACKAGE)
    if (LoadBookFile(book, path(DATADIR) / PACKAGE / fileName))
        return;
#endif
    throw SgException("Could not find opening book.");
}

std::string FuegoMainUtil::Version()
{
    ostringstream s;
#ifdef VERSION
    s << VERSION;
#else
    s << "(" __DATE__ ")";
#endif
#ifdef SVNREV
    s << "(" SVNREV ")";
#endif
#ifndef NDEBUG
    s << " (dbg)";
#endif
    return s.str();
}

//----------------------------------------------------------------------------
