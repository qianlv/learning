#!/usr/bin/python
#encoding=utf-8

import CoreGraphics
def pageCount(pdfPath):
    pdf = CoreGraphics.CGPDFDocumentCreateWithProvider(
            CoreGraphics.CGDataProviderCreateWithFilename(pdfPath)
            )
    return pdf.getNumberOfPages()

if __name__ =='__main__':
    import sys
    for path in sys.argv[1:]:
        print pageCount(path)
