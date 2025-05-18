cmake_minimum_required(VERSION 3.13)
project(libxpdf)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -emit-llvm -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -emit-llvm -O3")

set(XPDF_SOURCES
    repo/goo/FixedPoint.cc
    repo/goo/GHash.cc
    repo/goo/gmem.cc
    repo/goo/GString.cc
    repo/goo/gfile.cc
    repo/goo/GList.cc
    repo/goo/gmempp.cc
    repo/fofi/FoFiBase.cc
    repo/fofi/FoFiIdentifier.cc
    repo/fofi/FoFiType1.cc
    repo/fofi/FoFiEncodings.cc
    repo/fofi/FoFiTrueType.cc
    repo/fofi/FoFiType1C.cc
    repo/xpdf/Array.cc
    repo/xpdf/Annot.cc
    repo/xpdf/Lexer.cc
    repo/xpdf/Catalog.cc
    repo/xpdf/Stream.cc
    repo/xpdf/Object.cc
    repo/xpdf/TextString.cc
    repo/xpdf/Dict.cc
    repo/xpdf/Error.cc
    repo/xpdf/Page.cc
    repo/xpdf/Parser.cc
    repo/xpdf/PDFDoc.cc
    repo/xpdf/UTF8.cc
    repo/xpdf/XRef.cc
    repo/xpdf/GfxFont.cc
    repo/xpdf/Link.cc
    repo/xpdf/GlobalParams.cc
    repo/xpdf/CharCodeToUnicode.cc
    repo/xpdf/PSTokenizer.cc
    repo/xpdf/NameToCharCode.cc
    repo/xpdf/UnicodeMap.cc
    repo/xpdf/UnicodeRemapping.cc
    repo/xpdf/FontEncodingTables.cc
    repo/xpdf/PDFDocEncoding.cc
    repo/xpdf/BuiltinFontTables.cc
    repo/xpdf/BuiltinFont.cc
    repo/xpdf/CMap.cc
    repo/xpdf/OptionalContent.cc
    repo/xpdf/JBIG2Stream.cc
    repo/xpdf/JPXStream.cc
    repo/xpdf/JArithmeticDecoder.cc
    repo/xpdf/Decrypt.cc
    repo/xpdf/SecurityHandler.cc
    repo/xpdf/XFAScanner.cc
    repo/xpdf/AcroForm.cc
    repo/xpdf/Zoox.cc
)

add_library(xpdf STATIC ${XPDF_SOURCES})

target_include_directories(xpdf PUBLIC
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/repo/fofi
    ${CMAKE_SOURCE_DIR}/repo/goo
    ${CMAKE_SOURCE_DIR}/repo/xpdf
    ${CMAKE_SOURCE_DIR}/repo/splash
)
