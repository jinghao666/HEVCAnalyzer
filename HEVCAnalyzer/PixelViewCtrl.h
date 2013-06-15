#ifndef PIXELVIEWCTRL_H_INCLUDED
#define PIXELVIEWCTRL_H_INCLUDED
#define TIMER_ID  wxID_HIGHEST+100 

#include "HEVCAnalyzer.h"
#include "wx/timer.h"

class PixelViewCtrl : public wxScrolledWindow
{
    public:
        DECLARE_DYNAMIC_CLASS(PixelViewCtrl);
        PixelViewCtrl(){}
        PixelViewCtrl(wxWindow *parent, wxWindowID id)
            :wxScrolledWindow(parent, id), m_FocusPos(10, 10),
            m_iCUHeight(32), m_iCUWidth(32), m_iHeightPerPixel(70),
            m_iWidthPerPixel(50), m_bHexFormat(true), m_bScrollMode(false), 
            m_iXOffset(20), m_iYOffset(20)
        {
            SetBackgroundStyle(wxBG_STYLE_CUSTOM);
            //SetBackgroundStyle(wxBG_STYLE_COLOUR);
            //SetBackgroundColour(*wxWHITE);
            SetScrollRate(5, 7);
            SetVirtualSize(2*m_iXOffset+m_iCUWidth*m_iWidthPerPixel,
                           2*m_iYOffset+m_iCUHeight*m_iHeightPerPixel);
            m_pTimer = new wxTimer(this, TIMER_ID);
        }

        void OnDraw(wxDC&);
        void OnEraseBkg(wxEraseEvent& event);
        void DrawGrid(wxDC& dc, int xstart, int ystart, int xend, int yend);
        void DrawFocusLine(wxDC& dc);
        void DrawBackground(wxDC& dc, int xstart, int ystart, int xend, int yend);
        void OnMouseMove(wxMouseEvent& event);
        void OnMouseMidUp(wxMouseEvent& event);
        void OnTimer(wxTimerEvent& event);
        void OnLeaveWindow(wxMouseEvent& event);
        void OnEnterWindow(wxMouseEvent& event);
        void OnLeftButtonDown(wxMouseEvent& event);
        void OnLeftButtonUp(wxMouseEvent& event);

        void SetFocusPos(const wxPoint& pos);
        void SetCUHeight(const int height){m_iCUHeight = height;}
        void SetCUWidth(const int width){m_iCUWidth = width;}
        void SetHeight(const int height){m_iHeightPerPixel = height;}
        void SetWidth(const int width){m_iWidthPerPixel = width;}
        void ShowOneCell(wxDC& dc, const int xIndex, const int yIndex,
                         const int y, const int u, const int v);
        void LogicPosToIndex(int xLogic, int yLogic, int *xIndex, int *yIndex);

        int GetHeight()const{return m_iHeightPerPixel;}
        int GetWidth()const{return m_iWidthPerPixel;}
    private:
        wxPoint         m_FocusPos;
        int             m_iCUHeight;
        int             m_iCUWidth;
        int             m_iHeightPerPixel;
        int             m_iWidthPerPixel;
        bool            m_bHexFormat;
        bool            m_bScrollMode;
        int             m_iXCurrentUnit;
        int             m_iYCurrentUnit;
        int             m_iXStep;
        int             m_iYStep;
        wxTimer*        m_pTimer;
        int             m_iXOffset;
        int             m_iYOffset;
        wxPoint         m_LeftDownPos;

        DECLARE_EVENT_TABLE();
};

#endif