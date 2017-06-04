// mortgage_main.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <math.h>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include "date.h"

using namespace std;


	Fl_Window* win;
	Fl_Window* win1;
	
	// Input Wigets
	Fl_Float_Input* pin;
	Fl_Float_Input* rin;
	Fl_Float_Input* tin;
	Fl_Button* cal;
	Fl_Check_Button* mktab;
	Fl_Button* dok;
	Fl_Button* b_ex;
	
	// Output Wiget
	Fl_Value_Output* mopay;
	Fl_Value_Output* copoint;
	
	struct INFO {
	Fl_Input* gfn;
	Fl_Input* ent_date;
};

	// Forward Declares
	void mk_table_header();
	void mk_table_labels();
	void mk_ma_table();
	void mkmorttable();
	
	// Global Variables
	INFO dptr;
	double principal;
	double rate;
	double term_yrs;
	int    term_mos;
	double mort_pay;
	bool mkatab;
	double cop;
	string fname {""};
	string due_date;


// Calculate monthly payment

double cal_mp(double p, double r, int t) {
	r /= 1200;
	double mp;
	mp = p*r*(1-1/(1-pow(1+r,t)));
	return mp;
}

// Calcuate Crossover Poinnt
double calcop(double princ, double mrate, double mp){
	return (log(mp/(2*(mp-princ*mrate)))/log(1+mrate)+1);
}

void exit_cb(Fl_Widget *w, void* data) {
	exit(0);
};

void date_fn_cb(Fl_Widget *w, void* data) {
	
	fname = dptr.gfn->value();
	due_date = dptr.ent_date->value();
	win1->hide();
	// Make the Amortazition Table
	if (fname != "") {
		// Write table to file
		cout << "Write table to file \"fname\".\n";
		mkmorttable();
	}
	else
		//Write table to stdout
		mkmorttable();
	
}

void cal_cb(Fl_Widget* w, void* data) {

	// Get values from wigets
	principal = atof(pin->value());
	rate = atof(rin->value());
	term_yrs = atof(tin->value());
	term_mos = (term_yrs * 12 + 0.5);
	mkatab = mktab->value();
	
	// Calculate Monthy Payment
	mort_pay = cal_mp(principal, rate, term_mos);
	mopay->value(mort_pay);
	
	// Calulate Cross Point
	cop = calcop(principal, rate/1200, mort_pay);
	if (cop > 0.1) copoint->value(cop);
	
	// Make Table ??
	if (mkatab) win1->show();
}

void mk_table_header() {

	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    auto now = std::put_time(&tm, "%m/%d/%Y %H:%M:%S");

	cout << '#' << setw(48) << right << "Amortizaton Table" << endl;
	cout << "#\n";
	cout << "# Principal = $" << principal << endl;
	cout << "# Rate = " << rate << " percent." << endl;
	cout << "# Monthy Payment = $" << fixed << setprecision(2) << mort_pay << endl;
	cout << "# Crossover Point = ";
	(cop > 0.1) ? cout << '$' << cop : cout << "None";
	cout << "\n#" << endl;
	cout << "# Date-Time: " << now << endl;
	cout << "#\n";	
}

void mk_table_labels() {
	cout << setw(6) << "#PayNo" 
		<< setw(13) << right << "Payment Date"
		<< setw(15) << right << "Current Equity" 
		<< setw(17) << right << "Current Interest"
		<< setw(13) << right << "Tot. Equity" 
		<< setw(15) << right << "Tot. Interest" << endl;
}

void mk_ma_table() {
	double p {principal}; // begining load balance
	double r {rate/1200}; // rate per month
	double mp {mort_pay}; // monthy payment
	int t {term_mos};
	double cur_b {p};
	double cur_int;
	double cur_eq;
	double tot_eq;
	double tot_int;


	Date* dd = new Date(due_date);
	
	for(int i=1;i<=t;++i) {
		cur_int = cur_b*r;
		cur_eq = mp-cur_int;
		tot_int += cur_int;
		tot_eq += cur_eq;
		cur_b -= cur_eq;
		
		const int colw{14};
		cout << setw(4) << i
			<< setw(colw) << right << dd->get()
			<< setw(colw) << right << cur_eq
			<< setw(colw) << right << cur_int
			<< setw(colw) << right << tot_eq
			<< setw(colw) << right << tot_int<< endl;
			dd->add_month();		
	}
	delete dd;
}

void mkmorttable() {
	// Make the Amortazition Table
	
	mk_table_header();
	mk_table_labels();
	mk_ma_table();

}

int main(int argc, char** argv) {
	
	int x=125, y=10, w=150, h=25;
	win = new Fl_Window(340,280,"Mortgage Calculator");
	win->begin();
	pin = new Fl_Float_Input(x,y,w,h, "Principal");
	y += 27;
	rin = new Fl_Float_Input(x,y,w,h, "Rate(%)");
	y += 27;
	tin = new Fl_Float_Input(x,y,w,h, "Term(yrs)");
	y += 27;
	mopay = new Fl_Value_Output(x,y,w,h, "Payment(mo)");
	mopay->precision(2);
	y += 27;
	copoint = new Fl_Value_Output(x,y,w,h, "Cross Over Point");
	copoint->precision(2);
	y += 27;
	mktab = new Fl_Check_Button(x,y,w,h, "Make Amortization Table");
	y += 27;x += 100;
	cal = new Fl_Button(x,y,100,h,"Calculate");
	cal->shortcut(FL_Enter);
	y += 27;
	cal->callback(cal_cb);
	b_ex = new Fl_Button(x,y,100,h, "Exit");
	b_ex->callback(exit_cb);	
	win->end(); 
	
	// Make dialog window  
	win1 = new Fl_Window(340,100,"Get Payment Due Date");
	win1->begin();
	x=125,y=10,w=150,h=25;
	dptr.gfn = new Fl_Input(x,y,w,h,"File Name");
	y += 27;
	dptr.ent_date = new Fl_Input(x,y,w,h,"mm/dd/yyyy");
	y += 27; x +=100;
	dok = new Fl_Button(x,y,25,h, "OK");
	dok->callback(date_fn_cb);
	win1->end();
	  
	win->show(argc, argv);	
	return Fl::run();
}
