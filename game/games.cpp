#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define pii pair<int,int>
using namespace std;

#ifdef _WIN32
extern "C" int __stdcall Beep(unsigned long freq, unsigned long dur);
#endif

int lang=0;
string T(string zh,string en,string jp,string de){
	if(lang==0) return zh;
	if(lang==1) return en;
	if(lang==2) return jp;
	return de;
}

bool flagai,flagply;
int ai,ply;
map<string,int> too;

bool immersive = true;
int gameSpeed = 1;
bool muted = false;
bool enableAnim = true;
int defaultDifficulty = 2;

void sleep_ms(int ms);
int sp(int ms){
	if(gameSpeed == 0) return max(1LL, (long long)ms / 3);
	if(gameSpeed == 2) return ms * 2;
	return ms;
}
void sdelay(int ms){ sleep_ms(sp(ms)); }

int d[31][5]={{0,0,0,0,0},
				{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
				{1,0,0,0,0},{0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1},
				{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,2,0,0},{0,0,2,0,0},
				{0,1,0,1,0},{1,0,0,0,1},{0,0,0,0,0},{1,1,0,1,1},{0,1,2,1,0},
				{1,0,2,0,1},{1,1,2,1,0},{0,1,2,1,1},{0,0,9999,0,0},{0,0,0,0,0},
				{1,1,4,1,1},{0,2,4,2,0},{2,0,4,0,2},{1,1,9999,1,1},{1,2,4,2,1}};
int need[]={0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,3,4,3,3,4,4,3,3,6,6,6,7,8};

string toz[]={"","上躲","左躲","右躲","下躲","攒","上点","左点","中点","右点","下点",
              "左拳","右拳","单防","双拳","双枪","双枪左右","双枪上下","双防","乾坤",
              "横劈","竖劈","天崩","地裂","中戳","金身",
              "横劈竖劈","双横劈","双竖劈","乾坤中戳","天崩地裂"};
string toe[]={"","Dodge Up","Dodge Left","Dodge Right","Dodge Down","Charge",
              "Poke Up","Poke Left","Poke Center","Poke Right","Poke Down",
              "L Punch","R Punch","Block","Double Punch","Double Spear",
              "Spear L/R","Spear U/D","Double Block","Qiankun",
              "H-Slash","V-Slash","Sky Collapse","Earth Split","Mid Pierce","Golden Body",
              "H+V Slash","Dual H-Slash","Dual V-Slash","Qiankun+Mid","Sky+Earth"};
string toj[]={"","上回避","左回避","右回避","下回避","チャージ","上突き","左突き","中突き","右突き","下突き",
              "左パンチ","右パンチ","ブロック","ダブルパンチ","ダブルスピア",
              "スピア左右","スピア上下","ダブルブロック","乾坤",
              "横斬り","縦斬り","天崩","地裂","中刺し","金身",
              "横縦斬り","双横斬り","双縦斬り","乾坤中刺し","天崩地裂"};
string tod[]={"","Ausw. Oben","Ausw. Links","Ausw. Rechts","Ausw. Unten","Aufladen",
              "Stich Oben","Stich Links","Stich Mitte","Stich Rechts","Stich Unten",
              "L. Hieb","R. Hieb","Blocken","Doppelhieb","Doppelspeer",
              "Speer L/R","Speer U/O","Doppelblock","Qiankun",
              "Waag. Hieb","Senkr. Hieb","Himmelssturz","Erdriss","Mittelstich","Goldkoerper",
              "W+S Hieb","Doppel W-Hieb","Doppel S-Hieb","Qiankun+Mittel","Himmel+Erde"};
string to(int x){
	if(lang==0) return toz[x];
	if(lang==1) return toe[x];
	if(lang==2) return toj[x];
	return tod[x];
}

int combineMoves(int m1, int m2){
	int lo=min(m1,m2), hi=max(m1,m2);
	if(lo==20 && hi==20) return 27;
	if(lo==21 && hi==21) return 28;
	if(lo==20 && hi==21) return 26;
	if(lo==19 && hi==24) return 29;
	if(lo==22 && hi==23) return 30;
	return -1;
}

string face(int t){
	string a[]={"(^o^)/","^_^","(^_^)v",":D","\\o/"};
	string b[]={"(T_T)","(;_;)","(>_<)","TAT","(x_x)"};
	string c[]={"(-_-)","(=_=)","(o_o)","(._.)","(-_-;)"};
	if(t==0) return a[rand()%5];
	if(t==1) return b[rand()%5];
	return c[rand()%5];
}
string cheer(int t){
	string az[]={"漂亮!","干得漂亮!","太强了!","好耶!","666"};
	string ae[]={"Nice!","Well done!","Great!","Awesome!","666"};
	string aj[]={"いいね!","お見事!","すごい!","やった!","666"};
	string ad[]={"Schoen!","Gut gemacht!","Super!","Klasse!","666"};
	string bz[]={"再接再厉!","别灰心!","下次一定!","加油!","稳住!"};
	string be[]={"Keep going!","Don't give up!","Next time!","Cheer up!","Steady!"};
	string bj[]={"頑張れ!","元気出して!","次こそ!","ドンマイ!","落ち着け!"};
	string bd[]={"Weiter so!","Nicht aufgeben!","Naechstes Mal!","Kopf hoch!","Ruhig!"};
	string cz[]={"势均力敌","难分高下","无事发生","不相上下","接着来"};
	string ce[]={"Tie","Even match","Nothing happened","Close one","Next round"};
	string cj[]={"互角","引き分け","何もなし","五分五分","次へ"};
	string cd[]={"Gleichstand","Unentschieden","Nichts passiert","Ausgeglichen","Weiter"};
	int k=rand()%5;
	if(t==0){ if(lang==0)return az[k]; if(lang==1)return ae[k]; if(lang==2)return aj[k]; return ad[k]; }
	if(t==1){ if(lang==0)return bz[k]; if(lang==1)return be[k]; if(lang==2)return bj[k]; return bd[k]; }
	if(lang==0)return cz[k]; if(lang==1)return ce[k]; if(lang==2)return cj[k]; return cd[k];
}

void sleep_ms(int ms){ this_thread::sleep_for(chrono::milliseconds(ms)); }
void wait(int x){ for(int i=1;i<=x*100000;i++){} }

void beep(int freq, int dur){
	if(muted) return;
#ifdef _WIN32
	Beep(freq, dur);
#else
	cout << "\a"; cout.flush();
	this_thread::sleep_for(chrono::milliseconds(dur));
#endif
}
void snd_click()  { beep(900, 20); }
void snd_hit()    { beep(500, 60); }
void snd_win()    { beep(660,120); beep(880,120); beep(1320,200); }
void snd_lose()   { beep(440,150); beep(330,150); beep(220,250); }
void snd_ach()    { beep(1320,80); beep(1760,80); beep(2200,180); }
void snd_charge()  { beep(700,40);  beep(900,40); }
void snd_punch()   { beep(280,70); }
void snd_slash()   { beep(1400,50); beep(900,40); }
void snd_pierce()  { beep(1800,30); beep(2400,60); }
void snd_golden()  { beep(880,100); beep(1100,150); beep(1320,200); }
void snd_dual()    { beep(600,50);  beep(800,50);  beep(1000,70); }
void snd_move(int moveId){
	if(!immersive){ snd_click(); return; }
	if(moveId==5) snd_charge();
	else if(moveId>=6 && moveId<=10) snd_pierce();
	else if(moveId>=11 && moveId<=12) snd_punch();
	else if(moveId==13||moveId==18) { beep(400,50); }
	else if(moveId==14||(moveId>=15&&moveId<=17)) snd_punch();
	else if(moveId>=19 && moveId<=23) snd_slash();
	else if(moveId==24) snd_pierce();
	else if(moveId==25) snd_golden();
	else if(moveId>=26) snd_dual();
	else snd_click();
}

struct Stats {
	int hsW=0, hsL=0;
	int rpsW=0, rpsL=0, rpsD=0;
	int gmW=0, gmL=0, gmD=0;
	int mzW=0;
	int sqW=0, sqL=0;
	int lbW=0, lbL=0;
	int streakW=0, streakL=0, maxStreakW=0;
	bool tutHS=false, tutRPS=false, tutGM=false, tutMZ=false, tutSQ=false, tutLB=false;
} stats;

map<string,bool> ach;
vector<string> achOrder;

string achName(const string &k){
	if(k=="oneshot")  return T("一回合秒杀","One-turn kill","一撃必殺","Ein-Zug-Kill");
	if(k=="gomoku")   return T("五子连珠","Five in a row","五目並べ","Fuenf in Reihe");
	if(k=="maze30")   return T("闪电迷宫(30步内)","Speed Maze (<=30)","速攻迷路(30歩以内)","Blitzlabyrinth (<=30)");
	if(k=="demon")    return T("雷霆克星","Demon Slayer","悪魔退治","Daemonenjaeger");
	if(k=="streak10") return T("十连胜","10-win streak","10連勝","10er-Serie");
	if(k=="comeback") return T("绝境翻盘","Comeback","大逆転","Comeback");
	if(k=="perfect")  return T("完美格挡","Perfect Block","完全防御","Perfekte Parade");
	if(k=="golden5")  return T("金身逃杀","Golden Escape","金身脱出","Goldene Flucht");
	if(k=="bluff")    return T("老千大师","Master Bluffer","ブラフの達人","Bluff-Meister");
	if(k=="devil")    return T("魔鬼代言人","Devil's Advocate","悪魔の代弁者","Anwalt des Teufels");
	return k;
}

string rankName(){
	int w = stats.hsW;
	if(w < 5)  return T("青铜","Bronze","ブロンズ","Bronze");
	if(w < 15) return T("白银","Silver","シルバー","Silber");
	if(w < 30) return T("黄金","Gold","ゴールド","Gold");
	if(w < 50) return T("铂金","Platinum","プラチナ","Platin");
	return T("雷霆","Thunder","サンダー","Donner");
}
string rankColor(){
	int w = stats.hsW;
	if(w < 5)  return "\033[1;33m";
	if(w < 15) return "\033[1;37m";
	if(w < 30) return "\033[1;93m";
	if(w < 50) return "\033[1;96m";
	return "\033[1;91m";
}

void unlock(const string &k){
	if(ach[k]) return;
	ach[k] = true;
	achOrder.push_back(k);
	snd_ach();
	cout << endl;
	cout << "  \033[1;93m★★★ " << T("成就解锁!","ACHIEVEMENT!","実績解除!","ERFOLG!") << " ★★★\033[0m" << endl;
	cout << "  \033[1;93m      " << achName(k) << "\033[0m" << endl;
	sleep_ms(900);
}

void saveStats(){
	ofstream f("stats.txt");
	if(!f) return;
	f << stats.hsW << " " << stats.hsL << "\n";
	f << stats.rpsW << " " << stats.rpsL << " " << stats.rpsD << "\n";
	f << stats.gmW << " " << stats.gmL << " " << stats.gmD << "\n";
	f << stats.mzW << "\n";
	f << stats.sqW << " " << stats.sqL << "\n";
	f << stats.lbW << " " << stats.lbL << "\n";
	f << stats.streakW << " " << stats.streakL << " " << stats.maxStreakW << "\n";
	f << stats.tutHS << " " << stats.tutRPS << " " << stats.tutGM << " " << stats.tutMZ << " " << stats.tutSQ << " " << stats.tutLB << "\n";
	f << ach.size() << "\n";
	for(auto &p : ach) f << p.first << " " << p.second << "\n";
	f << (muted ? 1 : 0) << "\n";
	f << (enableAnim ? 1 : 0) << " " << defaultDifficulty << "\n";
}
void loadStats(){
	ifstream f("stats.txt");
	if(!f) return;
	f >> stats.hsW >> stats.hsL;
	f >> stats.rpsW >> stats.rpsL >> stats.rpsD;
	f >> stats.gmW >> stats.gmL >> stats.gmD;
	f >> stats.mzW;
	f >> stats.sqW >> stats.sqL;
	f >> stats.lbW >> stats.lbL;
	f >> stats.streakW >> stats.streakL >> stats.maxStreakW;
	f >> stats.tutHS >> stats.tutRPS >> stats.tutGM >> stats.tutMZ >> stats.tutSQ >> stats.tutLB;
	int n; if(f >> n){
		for(int i=0;i<n;i++){
			string k; int v; f >> k >> v;
			if(v) { ach[k]=true; achOrder.push_back(k); }
		}
	}
	int mm; if(f >> mm) muted = (mm != 0);
	int ea, dd; if(f >> ea >> dd){ enableAnim = (ea != 0); defaultDifficulty = dd; }
}

void showBoard(){
	cout << endl << "==========================================" << endl << endl;
	cout << "  \033[1;93m" << T("战 绩 记 录","SCOREBOARD","戦績","PUNKTE") << "\033[0m" << endl << endl;
	cout << "  " << T("段位","Rank","ランク","Rang") << ": " << rankColor() << rankName() << "\033[0m" << endl << endl;
	cout << "  " << T("拍手","Hand Slap","拍手","Klatsch") << "   " << T("胜","W","勝","S") << " " << stats.hsW << "  " << T("负","L","負","N") << " " << stats.hsL << endl;
	cout << "  " << T("石头剪刀布","RPS","じゃんけん","SSP") << "  " << T("胜","W","勝","S") << " " << stats.rpsW << "  " << T("负","L","負","N") << " " << stats.rpsL << "  " << T("平","D","分","U") << " " << stats.rpsD << endl;
	cout << "  " << T("五子棋","Gomoku","五目","Gomoku") << "  " << T("胜","W","勝","S") << " " << stats.gmW << "  " << T("负","L","負","N") << " " << stats.gmL << "  " << T("平","D","分","U") << " " << stats.gmD << endl;
	cout << "  " << T("迷宫通关","Maze cleared","迷路クリア","Labyrinth") << "  " << stats.mzW << endl;
	cout << "  " << T("鱿鱼","Squid","イカ","Squid") << "  " << T("胜","W","勝","S") << " " << stats.sqW << "  " << T("负","L","負","N") << " " << stats.sqL << endl;
	cout << "  " << T("骗子酒馆","Liar's Bar","ライアーズバー","Luegnerbar") << "  " << T("胜","W","勝","S") << " " << stats.lbW << "  " << T("负","L","負","N") << " " << stats.lbL << endl;
	cout << "  \033[1;96m" << T("当前连胜","Current streak","連勝中","Serie") << ": " << stats.streakW << "  |  " << T("最高连胜","Max streak","最高連勝","Bestserie") << ": " << stats.maxStreakW << "\033[0m" << endl;
	cout << endl << "  \033[1;95m" << T("已解锁成就:","Achievements:","解除済実績:","Erfolge:") << " " << ach.size() << "/10\033[0m" << endl;
	if(!achOrder.empty()){
		cout << endl;
		for(auto &k : achOrder){ cout << "    \033[1;93m★\033[0m " << achName(k) << endl; }
	}
	cout << endl << "==========================================" << endl;
	sleep_ms(800);
}

vector<string> LOGO = {
	"   ___           _        __  __ _             ",
	"  / __| __ _ _ _(_)_ _   |  \\/  (_)_ _  ___ ___ ",
	" | (_ |/ _` | '_| | ' \\  | |\\/| | | ' \\/ -_) _ \\",
	"  \\___|\\__,_|_| |_|_||_| |_|  |_|_|_||_\\___\\___/",
	"                                                "
};

void intro(){
	cout << "\033[2J\033[H"; cout.flush();
	for(int i=0;i<(int)LOGO.size();i++){
		cout << "\033[1;93m" << LOGO[i] << "\033[0m" << endl;
		cout.flush(); sleep_ms(90);
	}
	cout << endl; sleep_ms(250);
	beep(660,80);
	vector<pair<string,string>> subs = {
		{"        *  休 闲 小 游 戏  *",         "\033[1;93m"},
		{"        *  CASUAL MINI GAMES  *",      "\033[1;96m"},
		{"        *  カジュアルゲーム  *",       "\033[1;95m"},
		{"        *  GELEGENHEITSSPIEL  *",      "\033[1;92m"},
	};
	for(auto &p : subs){
		for(char c : p.first){
			cout << p.second << c << "\033[0m";
			cout.flush(); sleep_ms(10);
		}
		cout << endl; sleep_ms(80);
	}
	cout << endl; sleep_ms(250);
	cout << "  \033[1;97m[\033[0m";
	for(int i=0;i<40;i++){
		if(i<15)      cout << "\033[1;92m#\033[0m";
		else if(i<30) cout << "\033[1;93m#\033[0m";
		else          cout << "\033[1;91m#\033[0m";
		cout.flush(); sleep_ms(20);
	}
	cout << "\033[1;97m]\033[0m  \033[1;92mREADY!\033[0m" << endl;
	beep(1320,150);
	cout << endl; sleep_ms(500);
	cout << "\033[2J\033[H";
}

void outro(){
	beep(880,100); beep(660,100);
	cout << "\033[2J\033[H";
	cout << endl << endl << endl << endl << endl;
	cout << "        \033[1;90m*  T H A N K S   F O R   P L A Y I N G  *\033[0m" << endl;
	sleep_ms(400);
	cout << endl << endl;

	int lines = (int)LOGO.size();
	cout << "\033[?25l";
	for(int i=lines-1; i>=0; i--){
		cout << "\033[10;1H";
		for(int j=0;j<=i;j++) cout << "\033[1;93m" << LOGO[j] << "\033[0m" << endl;
		for(int j=i+1;j<lines;j++) cout << "                                                 " << endl;
		cout.flush();
		sleep_ms(80);
	}
	cout << "\033[?25h";

	cout << endl << endl;
	cout << "  \033[1;97m[\033[0m";
	for(int i=40;i>0;i--){
		if(i>25)      cout << "\033[1;91m \033[0m";
		if(i<=25 && i>10) cout << "\033[1;93m \033[0m";
		if(i<=10)     cout << "\033[1;92m \033[0m";
		cout.flush(); sleep_ms(15);
	}
	cout << "\033[1;97m]\033[0m  \033[1;91mBYE!\033[0m" << endl;
	beep(440,200); beep(330,200); beep(220,300);
	cout << endl;
	sleep_ms(600);
}

void confetti(){
	if(!enableAnim) return;
	vector<string> ch = {"*", ".", "+", "o", "x", "0"};
	vector<string> co = {"\033[1;93m","\033[1;96m","\033[1;95m","\033[1;92m","\033[1;91m","\033[1;97m"};
	for(int frame=0; frame<15; frame++){
		cout << "\033[s";
		for(int i=0;i<30;i++){
			int row = rand()%22 + 1;
			int col = rand()%72 + 1;
			cout << "\033[" << row << ";" << col << "H";
			cout << co[rand()%co.size()] << ch[rand()%ch.size()] << "\033[0m";
		}
		cout << "\033[u";
		cout.flush();
		sleep_ms(80);
	}
	cout << "\033[s";
	for(int i=0;i<60;i++){
		int row = rand()%22 + 1;
		int col = rand()%72 + 1;
		cout << "\033[" << row << ";" << col << "H ";
	}
	cout << "\033[u";
	sleep_ms(200);
	cout << "\033[2J\033[H";
}

void announce(bool win){
	if(!immersive){
		cout << endl << "  >>> " << (win ? T("你赢了!","You win!","勝ち!","Du gewinnst!") : T("你输了!","You lose!","負け!","Du verlierst!")) << endl;
		sleep_ms(400);
		return;
	}
	confetti();
	string bg = win ? "\033[48;5;220m\033[30m" : "\033[48;5;196m\033[97m";
	string line1 = win
		? T("  *  *  *     你  赢  了 !     *  *  *  ","  *  *  *     YOU  WIN !     *  *  *  ","  *  *  *     勝  ち !     *  *  *  ","  *  *  *     DU  GEWINNST !     *  *  *  ")
		: T("  x  x  x     你  输  了 !     x  x  x  ","  x  x  x     YOU  LOSE !     x  x  x  ","  x  x  x     負  け !     x  x  x  ","  x  x  x     DU  VERLIERST !     x  x  x  ");
	string line2 = face(win ? 0 : 1);
	cout << "\033[2J\033[H";
	cout << bg;
	for(int i=0;i<12;i++) cout << string(78,' ') << "\n";
	cout << "           " << line1 << "\n\n";
	cout << "                                 " << line2 << "\n";
	for(int i=0;i<12;i++) cout << string(78,' ') << "\n";
	cout << "\033[0m";
	cout.flush();
	if(win) snd_win(); else snd_lose();
	sleep_ms(900);
	cout << "\033[2J\033[H";
}

void tutorial(int g){
	if(g==1 && stats.tutHS) return;
	if(g==2 && stats.tutRPS) return;
	if(g==3 && stats.tutGM) return;
	if(g==4 && stats.tutMZ) return;
	if(g==5 && stats.tutSQ) return;
	if(g==6 && stats.tutLB) return;

	cout << endl << "==========================================" << endl << endl;
	cout << "  \033[1;93m" << T("新手教程","Tutorial","チュートリアル","Tutorial") << "\033[0m" << endl << endl;

	auto step=[&](const string &zh, const string &en, const string &jp, const string &de){
		cout << "  " << T(zh,en,jp,de) << endl;
		snd_click();
		sleep_ms(700);
	};

	if(g==1){
		step("第 1 步: 攒费 —— 按 z 攒 1 费","Step 1: Charge -- press z to gain 1 cost","ステップ1: チャージ -- z で 1 コスト","Schritt 1: Aufladen -- z fuer 1 Kosten");
		step("第 2 步: 花费用招 —— 费用够了就打","Step 2: Spend cost -- attack when you can afford","ステップ2: 消費 -- コストが足りたら攻撃","Schritt 2: Ausgeben -- angreifen wenn bezahlbar");
		step("第 3 步: 躲/防 —— wasd 躲, f 格挡","Step 3: Dodge/Block -- wasd to dodge, f to block","ステップ3: 回避/防御 -- wasd 回避, f ブロック","Schritt 3: Ausweichen/Blocken -- wasd, f");
		step("第 4 步: 中戳(j)对中秒杀, 金身(jj)挡中","Step 4: Mid Pierce(j) kills center, Golden(jj) blocks","ステップ4: 中刺し(j)中央即死, 金身(jj)防御","Schritt 4: Mittelstich(j) toetet Mitte, Goldkoerper(jj)");
		step("第 5 步: 双手势 —— 空格分隔两招(费用相加)","Step 5: Dual move -- space-separate two moves (sum cost)","ステップ5: 双手勢 -- スペース区切り (コスト合計)","Schritt 5: Doppelzug -- Leerzeichen (Kosten summieren)");
		step("第 6 步: 输入 ? 查看完整招式表","Step 6: Type ? for full move reference","ステップ6: ? で技一覧","Schritt 6: ? fuer Zug-Referenz");
		stats.tutHS = true;
	}
	if(g==2){
		step("输入 石头/布/剪刀 或 r/p/s","Type rock/paper/scissors or r/p/s","グー/パー/チョキ または r/p/s","Stein/Papier/Schere oder r/p/s");
		step("三局定胜负, 输入 q 退出","First to win -- q to quit","勝負あり -- q で終了","Best of -- q zum Beenden");
		stats.tutRPS = true;
	}
	if(g==3){
		step("输入 行 列 落子, 例如 6 F","Type row col, e.g. 6 F","行 列 を入力, 例 6 F","Zeile Spalte, z.B. 6 F");
		step("先连成 5 子者胜, 连成的子会变金色","Five in a row wins, gold highlight","5目並べたら勝ち, 金色に","Fuenf in Reihe gewinnt, gold");
		stats.tutGM = true;
	}
	if(g==4){
		step("用 WASD 从 S 走到 E","Use WASD to go from S to E","WASD で S から E へ","WASD von S nach E");
		step("墙是 #, 你是 @, 终点是 E","Wall is #, you are @, goal is E","壁 #, あなた @, ゴール E","Wand #, du @, Ziel E");
		step("30 步内通关有成就","Clear in 30 steps for an achievement","30 歩以内で実績","Unter 30 Schritten: Erfolg");
		stats.tutMZ = true;
	}
	if(g==5){
		step("绿灯(70%): 输入 走 前进 1 步","Green (70%): type go to advance 1","青(70%): go で 1 歩進む","Gruen (70%): go fuer 1 Schritt");
		step("红灯(30%): 输入 停 不动","Red (30%): type stop to stay","赤(30%): stop で止まる","Rot (30%): stop stehen bleiben");
		step("红灯时走 = 出局! 先到 15 者胜","Move on RED = out! First to 15 wins","赤で動くと失格! 先に 15 で勝ち","Bei Rot bewegen = raus! Zuerst 15");
		stats.tutSQ = true;
	}
	if(g==6){
		step("每人 3 命, 每轮 5 张手牌","3 lives, 5 cards per round","3 ライフ、毎回 5 枚","3 Leben, 5 Karten pro Runde");
		step("每轮随机目标: J / Q / K","Random target: J / Q / K","毎回ランダム: J / Q / K","Zufaelliges Ziel: J / Q / K");
		step("一次可出 1-3 张牌 (如 1 3 / 13 / 1,3 都行)","Play 1-3 cards (1 3 / 13 / 1,3 all OK)","1-3 枚出せる (1 3 / 13 / 1,3)","1-3 Karten (1 3 / 13 / 1,3)");
		step("JOKER 是万能牌, 永远算真","JOKER is wild, always counts","JOKER は万能、常に真","JOKER wild, immer wahr");
		step("魔鬼Q 只能当 Q, 翻开时质疑者 -2 命!","DevilQ only as Q, if revealed doubter -2!","デビルQ は Q のみ、開いたら疑った方 -2!","TeufelQ nur als Q, aufgedeckt Zweifler -2!");
		step("质疑翻开整叠: 有假 → 出牌者扣假牌数, 全真 → 质疑者 -1","Reveal stack: any lie -> player -lies, all true -> doubter -1","全開: 嘘→出した方-嘘数、真→疑った方-1","Aufdecken: Luege -> Spieler -Luegen, echt -> Zweifler -1");
		step("命归零淘汰, 最后一人胜。正常 2人 / 多人 4人","Lose all lives = out, last wins. Normal 2P / Multi 4P","ライフ 0 で脱落、最後が勝ち。2人 / 4人","Alle Leben weg = raus, letzter gewinnt. 2P / 4P");
		stats.tutLB = true;
	}
	cout << endl << "  \033[1;92m" << T("教程结束!","Tutorial done!","完了!","Fertig!") << "\033[0m" << endl;
	sleep_ms(800);
	saveStats();
}

map<string, map<int,int>> learnTable;
map<int,int> globalMoveCnt;
int lastPlyMove = 0;
int difficulty = 2;
int aiMood = 0;

const int MAX_LC = 6;
string encodeState(int a,int b,int c){
	int aa = min(a, (long long)MAX_LC);
	int bb = min(b, (long long)MAX_LC);
	return to_string(aa)+"_"+to_string(bb)+"_"+to_string(c);
}
void learn(int aiC,int plyC,int lastMv,int plyMove){
	globalMoveCnt[plyMove]++;
	learnTable[encodeState(aiC, plyC, lastMv)][plyMove]++;
}
int predict(int aiC,int plyC,int lastMv){
	string k = encodeState(aiC, plyC, lastMv);
	int thr = (difficulty >= 3) ? 1 : 2;
	auto it = learnTable.find(k);
	if(it != learnTable.end()){
		int best=-1, bc=0;
		for(auto &p : it->second){ if(p.second > bc){ bc=p.second; best=p.first; } }
		if(best>0 && bc>=thr) return best;
	}
	if(globalMoveCnt.empty()) return -1;
	int best=-1, bc=0;
	for(auto &p : globalMoveCnt){ if(p.second > bc){ bc=p.second; best=p.first; } }
	if(best>0 && bc>=3) return best;
	return -1;
}
void saveLearn(const string &file){
	ofstream fout(file); if(!fout) return;
	fout << learnTable.size() << "\n";
	for(auto &s : learnTable){
		fout << s.first << " " << s.second.size();
		for(auto &p : s.second) fout << " " << p.first << " " << p.second;
		fout << "\n";
	}
	fout << globalMoveCnt.size() << "\n";
	for(auto &p : globalMoveCnt) fout << p.first << " " << p.second << "\n";
}
void loadLearn(const string &file){
	ifstream fin(file); if(!fin) return;
	int n; if(!(fin >> n)) return;
	for(int i=0;i<n;i++){
		string k; int m; fin >> k >> m;
		for(int j=0;j<m;j++){ int a,b; fin >> a >> b; learnTable[k][a]=b; }
	}
	fin >> n;
	for(int i=0;i<n;i++){ int a,b; fin >> a >> b; globalMoveCnt[a]=b; }
}

const int DPC = 7;
const double GAMMA = 0.9;
double dpV[DPC][DPC][31];

int dpOutcome(int a, int p){
	int aiin=2, plyin=2;
	if(a==1)aiin=0; else if(a==2)aiin=1; else if(a==3)aiin=3; else if(a==4)aiin=4;
	if(p==1)plyin=0; else if(p==2)plyin=1; else if(p==3)plyin=3; else if(p==4)plyin=4;
	if(a==13 && d[p][aiin]==1) return 1;
	if(p==13 && d[a][plyin]==1) return 0;
	if(a==13 && d[p][aiin]==2) return -1;
	if(p==13 && d[a][plyin]==2) return -1;
	if(p==18) return 0;
	if(a==18) return 1;
	if((a==11||a==12||a==14) && plyin!=2) return 0;
	if((p==11||p==12||p==14) && aiin!=2) return 1;
	int aD = d[a][plyin], pD = d[p][aiin];
	if(p==25 && d[a][2]>0) aD = 0;
	if(a==25 && d[p][2]>0) pD = 0;
	if(aD == pD) return -1;
	if(aD > pD) return 1;
	return 0;
}
void dpPlayerDist(int plyC, int aiC, int lastMv, double* P){
	for(int i=0;i<31;i++) P[i]=0;
	double total = 0;
	for(int p=1; p<=30; p++){
		if(need[p] > plyC) continue;
		P[p] = 0.3; total += 0.3;
	}
	string k = encodeState(aiC, plyC, lastMv);
	auto it = learnTable.find(k);
	if(it != learnTable.end()){
		for(auto &kv : it->second){
			if(need[kv.first] > plyC) continue;
			P[kv.first] += kv.second; total += kv.second;
		}
	}
	for(auto &kv : globalMoveCnt){
		if(need[kv.first] > plyC) continue;
		P[kv.first] += kv.second * 0.1; total += kv.second * 0.1;
	}
	if(total < 1e-9){
		int cnt=0;
		for(int p=1;p<=30;p++) if(need[p]<=plyC) cnt++;
		if(cnt == 0) cnt = 1;
		for(int p=1;p<=30;p++) if(need[p]<=plyC) P[p]=1.0/cnt;
		return;
	}
	for(int p=1;p<=30;p++) P[p] /= total;
}
void dpSolve(){
	for(int i=0;i<DPC;i++) for(int j=0;j<DPC;j++) for(int k=0;k<31;k++) dpV[i][j][k]=0.0;
	for(int iter=0; iter<40; iter++){
		double md = 0;
		for(int aiC=0; aiC<DPC; aiC++)
		for(int plyC=0; plyC<DPC; plyC++)
		for(int lastMv=0; lastMv<31; lastMv++){
			double P[31]; dpPlayerDist(plyC, aiC, lastMv, P);
			double bestV = 0;
			for(int a=1; a<=30; a++){
				if(need[a] > aiC) continue;
				int naiC = aiC - need[a] + (a==5?1:0);
				naiC = max(0LL, min(naiC, (long long)(DPC-1)));
				double eV = 0;
				for(int p=1; p<=30; p++){
					if(need[p] > plyC) continue;
					if(P[p] < 1e-9) continue;
					int out = dpOutcome(a, p);
					if(out == 1) eV += P[p];
					else if(out == 0) {}
					else {
						int npC = plyC - need[p] + (p==5?1:0);
						npC = max(0LL, min(npC, (long long)(DPC-1)));
						eV += P[p] * GAMMA * dpV[naiC][npC][p];
					}
				}
				if(eV > bestV) bestV = eV;
			}
			double diff = fabs(bestV - dpV[aiC][plyC][lastMv]);
			if(diff > md) md = diff;
			dpV[aiC][plyC][lastMv] = bestV;
		}
		if(md < 1e-7) break;
	}
}
int dpPick(){
	int aiC = min(ai, (long long)(DPC-1));
	int plyC = min(ply, (long long)(DPC-1));
	int lastMv = lastPlyMove;
	double P[31]; dpPlayerDist(plyC, aiC, lastMv, P);
	double bestV = -1e18;
	vector<int> bestAs;
	for(int a=1; a<=30; a++){
		if(need[a] > ai) continue;
		int naiC = aiC - need[a] + (a==5?1:0);
		naiC = max(0LL, min(naiC, (long long)(DPC-1)));
		double eV = 0;
		for(int p=1; p<=30; p++){
			if(need[p] > ply) continue;
			if(P[p] < 1e-9) continue;
			int out = dpOutcome(a, p);
			if(out == 1) eV += P[p];
			else if(out == 0) {}
			else {
				int npC = plyC - need[p] + (p==5?1:0);
				npC = max(0LL, min(npC, (long long)(DPC-1)));
				eV += P[p] * GAMMA * dpV[naiC][npC][p];
			}
		}
		if(eV > bestV + 1e-9){ bestV = eV; bestAs.clear(); bestAs.push_back(a); }
		else if(fabs(eV - bestV) < 1e-9){ bestAs.push_back(a); }
	}
	if(bestAs.empty()){ for(int a=1;a<=30;a++) if(need[a]<=ai) bestAs.push_back(a); }
	if(rand() % 100 < 3){
		vector<int> usable;
		for(int a=1;a<=30;a++) if(need[a]<=ai) usable.push_back(a);
		if(!usable.empty()) return usable[rand()%usable.size()];
		return 5;
	}
	return bestAs[rand()%bestAs.size()];
}

void updateMood(bool playerWin){
	if(playerWin){
		stats.streakW++; stats.streakL=0;
		if(stats.streakW > stats.maxStreakW) stats.maxStreakW = stats.streakW;
		if(stats.streakW >= 3) aiMood = 1;
	} else {
		stats.streakL++; stats.streakW=0;
		if(stats.streakL >= 3) aiMood = -1;
	}
	if(stats.streakW == 10) unlock("streak10");
}

int tryDualMove(int plydo){
	if(ai < 6) return -1;
	int dualChance = 0;
	if(difficulty == 2) dualChance = 8;
	else if(difficulty == 3) dualChance = 20;
	else if(difficulty == 4) dualChance = 40;
	else return -1;
	if((int)(rand()%100) >= dualChance) return -1;
	vector<int> duals;
	for(int m=26; m<=30; m++) if(need[m] <= ai) duals.push_back(m);
	if(duals.empty()) return -1;
	vector<int> wins;
	for(int m : duals) if(dpOutcome(m, plydo) == 1) wins.push_back(m);
	if(!wins.empty()) return wins[rand()%wins.size()];
	return duals[rand()%duals.size()];
}

int chooseAI(int plydo){
	if(difficulty == 2 || difficulty == 3 || difficulty == 4){
		int dm = tryDualMove(plydo);
		if(dm > 0) return dm;
	}
	if(difficulty == 5){
		if(rand() % 100 < 5){
			vector<int> usable;
			for(int a=1; a<=30; a++) if(need[a] <= ai) usable.push_back(a);
			if(!usable.empty()) return usable[rand() % usable.size()];
			return 5;
		}
		vector<int> winMoves, tieMoves;
		for(int a=1; a<=30; a++){
			if(need[a] > ai) continue;
			int out = dpOutcome(a, plydo);
			if(out == 1) winMoves.push_back(a);
			else if(out == -1) tieMoves.push_back(a);
		}
		vector<int> &pick = !winMoves.empty() ? winMoves : tieMoves;
		if(!pick.empty()){
			int best = pick[0];
			for(int m : pick) if(need[m] < need[best]) best = m;
			return best;
		}
		vector<int> usable;
		for(int a=1; a<=30; a++) if(need[a] <= ai) usable.push_back(a);
		if(!usable.empty()) return usable[rand() % usable.size()];
		return 5;
	}
	if(difficulty == 4){
		if(ai==0 && ply==0) return 5;
		dpSolve();
		return dpPick();
	}
	if(ai==0 && ply==0) return 5;
	if(ai==0){
		int baseP = (aiMood==1) ? 45 : (aiMood==-1) ? 15 : 25;
		int saveP = min(85LL, (long long)(baseP + ply * 15));
		if((int)(rand()%100) < saveP) return 5;
		return rand()%4+1;
	}
	if(difficulty==1){
		if(ai<=1) return rand()%13+1;
		if(ai<=2) return rand()%17+1;
		if(ai<=3) return rand()%21+1;
		return rand()%25+1;
	}
	int guess = predict(ai, ply, lastPlyMove);
	if(guess > 0){
		int explore = (difficulty >= 3) ? 10 : 25;
		if(aiMood==1) explore = max(5LL, explore-10);
		if(aiMood==-1) explore = min(40LL, explore+10);
		if((int)(rand()%100) >= explore){
			int gpos = 2;
			if(guess==1) gpos=0;
			else if(guess==2) gpos=1;
			else if(guess==3) gpos=3;
			else if(guess==4) gpos=4;
			vector<int> counters;
			for(int m=6; m<=30; m++){
				if(need[m] > ai) continue;
				if(m==13 && d[guess][2] >= 1 && d[guess][2] <= 2){ counters.push_back(m); continue; }
				if(d[m][gpos] > d[guess][2]) counters.push_back(m);
			}
			if(!counters.empty()){
				if(difficulty >= 3){
					sort(counters.begin(), counters.end(), [](int a,int b){
						if(d[a][2] != d[b][2]) return d[a][2] > d[b][2];
						return need[a] < need[b];
					});
				}else{
					sort(counters.begin(), counters.end(), [](int a,int b){ return need[a] < need[b]; });
				}
				return counters[0];
			}
		}
	}
	if(ai >= 1){
		vector<int> atk;
		for(int a=6; a<=30; a++) if(need[a] <= ai) atk.push_back(a);
		if(!atk.empty()){
			if(aiMood == -1 && rand()%100 < 30) return 13;
			return atk[rand() % atk.size()];
		}
	}
	if(ai<=1) return rand()%13+1;
	if(ai<=2) return rand()%17+1;
	if(ai<=3) return rand()%21+1;
	return rand()%25+1;
}

void init(int aido,int plydo){
	int aiin=2, plyin=2;
	ai-=(need[aido]); ply-=(need[plydo]);
	if(aido==5) ai++; if(plydo==5) ply++;
	if(aido==1)aiin=0; else if(aido==2)aiin=1; else if(aido==3)aiin=3; else if(aido==4)aiin=4;
	if(plydo==1)plyin=0; else if(plydo==2)plyin=1; else if(plydo==3)plyin=3; else if(plydo==4)plyin=4;
	if(aido==13&&d[plydo][aiin]==1){ flagply=0; return; }
	if(plydo==13&&d[aido][plyin]==1){ flagai=0; return; }
	if(aido==13&&d[plydo][aiin]==2){ return; }
	if(plydo==13&&d[aido][plyin]==2){ return; }
	if(plydo==18){ flagai=0; return; }
	if(aido==18){ flagply=0; return; }
	if((aido==11||aido==12||aido==14)&&plyin!=2){ flagai=0; return; }
	if((plydo==11||plydo==12||plydo==14)&&aiin!=2){ flagply=0; return; }
	int aD=d[aido][plyin], pD=d[plydo][aiin];
	if(plydo==25 && d[aido][2]>0) aD = 0;
	if(aido==25 && d[plydo][2]>0) pD = 0;
	if(aD==pD) return;
	if(aD>pD){ flagply=0; return; }
	flagai=0;
}

bool solve(int plydo, int aido, int rounds){
	if(flagai==0){
		cout<<"  >>> "<<T("你赢了! ","You win! ","勝ち! ","Du gewinnst! ")<<cheer(0)<<" "<<face(0)<<endl;
		if(rounds == 1) unlock("oneshot");
		if(plydo==25) unlock("golden5");
		sdelay(350); announce(true);
		return 0;
	}
	if(flagply==0){
		cout<<"  >>> "<<T("你输了! ","You lose! ","負け! ","Du verlierst! ")<<cheer(1)<<" "<<face(1)<<endl;
		sdelay(350); announce(false);
		return 0;
	}
	return 1;
}

void showMovesHelp(){
	cout << endl << "==========================================" << endl << endl;
	cout << "  \033[1;93m" << T("招式速查表","MOVE REFERENCE","技一覧","ZUG-REFERENZ") << "\033[0m" << endl << endl;
	cout << "  " << T("指令","Cmd","コマンド","Befehl") << "        " << T("费用","Cost","費","K") << "  " << T("上 左 中 右 下","U  L  C  R  D","上 左 中 右 下","O  L  M  R  U") << endl;
	cout << "  ----------------------------------------" << endl;
	auto row=[&](string cmd, int id){
		cout << "  " << left << setw(12) << cmd << setw(4) << need[id];
		for(int j=0;j<5;j++){
			if(d[id][j]==9999) cout << " \033[1;91m*  \033[0m";
			else cout << " " << d[id][j] << "  ";
		}
		cout << "  " << to(id) << endl;
	};
	cout << "  \033[1;90m" << T("— 0 费 —","— 0 cost —","— 0コスト —","— 0 Kosten —") << "\033[0m" << endl;
	row("w",1); row("a",2); row("d",3); row("s",4); row("z",5);
	cout << "  \033[1;90m" << T("— 1 费 —","— 1 cost —","— 1コスト —","— 1 Kosten —") << "\033[0m" << endl;
	row("8",6); row("4",7); row("5",8); row("6",9); row("2",10);
	row("71",11); row("93",12); row("f",13);
	cout << "  \033[1;90m" << T("— 2 费 —","— 2 cost —","— 2コスト —","— 2 Kosten —") << "\033[0m" << endl;
	row("4466",14); row("55",15); row("46",16); row("82",17);
	cout << "  \033[1;90m" << T("— 3 费 —","— 3 cost —","— 3コスト —","— 3 Kosten —") << "\033[0m" << endl;
	row("ff",18); row("456",20); row("852",21);
	row("j",24); row("jj",25);
	cout << "  \033[1;90m" << T("— 4 费 —","— 4 cost —","— 4コスト —","— 4 Kosten —") << "\033[0m" << endl;
	row("7913",19); row("79",22); row("13",23);
	cout << "  \033[1;95m" << T("— 双手势 (空格分隔) —","— DUAL (space-sep) —","— 双手勢 —","— DOPPELZUG —") << "\033[0m" << endl;
	row("456 852",26); row("456 456",27); row("852 852",28); row("7913 j",29); row("79 13",30);
	cout << endl;
	cout << "  " << T("\033[1;91m* = 秒杀中位\033[0m。中戳/j 命中非躲位直接秒杀",
	               "\033[1;91m* = instant kill at center\033[0m. Mid Pierce hits non-dodge",
	               "\033[1;91m* = 中央即死\033[0m。中刺しは回避以外に即死",
	               "\033[1;91m* = Mitte-Sofortkill\033[0m. Mittelstich toetet Nicht-Ausweicher") << endl;
	cout << "==========================================" << endl;
}

void playMoveAnimation(int moveId){
	if(!immersive){ cout << "  " << to(moveId) << endl; return; }
	switch(moveId){
		case 24: cout << "  \033[1;91m>>>---===>\033[0m \033[1;93m" << to(moveId) << "\033[0m" << endl; break;
		case 25: cout << "  \033[1;93m* * * G O L D E N * * *\033[0m " << to(moveId) << endl; break;
		case 20: case 26: case 27: cout << "  \033[1;93m======[斩]======\033[0m " << to(moveId) << endl; break;
		case 21: case 28: cout << "  \033[1;93m| | 斩 | |\033[0m " << to(moveId) << endl; break;
		case 29: cout << "  \033[1;91m~*~*~ 乾坤·中戳 ~*~*~\033[0m" << endl; break;
		case 30: cout << "  \033[1;91m# # #  天 崩 地 裂  # # #\033[0m" << endl; break;
		case 19: cout << "  \033[1;95m~*~*~ 乾 坤 ~*~*~\033[0m " << to(moveId) << endl; break;
		default: cout << "  " << to(moveId) << endl;
	}
}

string aiHint(){
	if(!immersive) return "";
	if(ai == 0) return T("  \033[1;90m[AI 正在攒费...]\033[0m","  \033[1;90m[AI is charging...]\033[0m","  \033[1;90m[AI がチャージ中...]\033[0m","  \033[1;90m[AI laedt auf...]\033[0m");
	if(aiMood == 1) return T("  \033[1;91m[AI 气势凌厉，像要强攻！]\033[0m","  \033[1;91m[AI looks aggressive!]\033[0m","  \033[1;91m[AI 攻撃的！]\033[0m","  \033[1;91m[AI ist aggressiv!]\033[0m");
	if(aiMood == -1) return T("  \033[1;96m[AI 谨慎防守，似在等你出手...]\033[0m","  \033[1;96m[AI is playing defensive...]\033[0m","  \033[1;96m[AI は慎重...]\033[0m","  \033[1;96m[AI spielt defensiv...]\033[0m");
	if(ai >= 4) return T("  \033[1;93m[AI 蓄势待发，恐有大招...]\033[0m","  \033[1;93m[AI is preparing something big...]\033[0m","  \033[1;93m[AI 大技を準備中...]\033[0m","  \033[1;93m[AI bereitet Grosses vor...]\033[0m");
	return T("  \033[1;90m[AI 静观其变...]\033[0m","  \033[1;90m[AI watches silently...]\033[0m","  \033[1;90m[AI は静観...]\033[0m","  \033[1;90m[AI beobachtet...]\033[0m");
}

void battleTheater(int aido, int plydo){
	cout << endl << "  \033[1;90m----------- 出招 -----------\033[0m" << endl;
	sdelay(150);
	cout << "  "; playMoveAnimation(plydo);
	snd_move(plydo);
	sdelay(350);
	cout << "  "; playMoveAnimation(aido);
	snd_move(aido);
	sdelay(350);
	cout << "  \033[1;90m-----------------------------\033[0m" << endl << endl;
}

void rps(){
	int w=0,l=0,dr=0;
	string nz[]={"石头","布","剪刀"};
	string ne[]={"Rock","Paper","Scissors"};
	string nj[]={"グー","パー","チョキ"};
	string nd[]={"Stein","Papier","Schere"};
	auto name=[&](int i)->string{
		if(lang==0) return nz[i];
		if(lang==1) return ne[i];
		if(lang==2) return nj[i];
		return nd[i];
	};
	cout<<endl<<"=========================================="<<endl<<endl;
	cout<<T("  石头剪刀布","  Rock Paper Scissors","  じゃんけん","  Schere Stein Papier")<<endl;
	cout<<T("  输入 石头/布/剪刀 或 r/p/s, q退出","  Type rock/paper/scissors or r/p/s, q to quit","  グー/パー/チョキ または r/p/s, q で終了","  Stein/Papier/Schere oder r/p/s, q zum Beenden")<<endl<<endl;
	cout<<"=========================================="<<endl;
	while(1){
		cout<<endl;
		cout<<T("  比分  你 ","  Score  You ","  スコア  あなた ","  Punktestand  Du ")<<w<<T("  AI ","  AI ","  AI ","  AI ")<<l<<T("  平局 ","  Draw ","  引き分け ","  Unentschieden ")<<dr<<endl<<endl;
		cout<<T("请出拳 (q退出): ","Your move (q quit): ","じゃんけんぽん (q終了): ","Dein Zug (q beenden): ");
		string s; if(!(cin>>s)){ cin.clear(); continue; }
		for(auto &c : s) c = tolower(c);
		if(s=="q"||s=="quit"||s=="exit") break;
		int me=-1;
		if(s=="r"||s=="rock"||s=="石头"||s=="グー"||s=="stein") me=0;
		if(s=="p"||s=="paper"||s=="布"||s=="パー"||s=="papier") me=1;
		if(s=="s"||s=="scissors"||s=="剪刀"||s=="チョキ"||s=="schere") me=2;
		if(me<0){ cout<<endl<<T("  无效输入,请重新输入","  Invalid input, try again","  無効な入力、もう一度","  Ungueltige Eingabe, nochmal")<<endl; continue; }
		snd_click();
		int y=rand()%3;
		cout<<endl<<"------------------------------------------"<<endl<<endl;
		cout<<"  "<<T("[你]","[You]","[あなた]","[Du]")<<"  "<<name(me)<<endl<<endl;
		cout<<"  [AI]  "<<name(y)<<endl<<endl;
		cout<<"------------------------------------------"<<endl<<endl;
		if(me==y){ cout<<"  >>> "<<T("平局! ","Draw! ","引き分け! ","Unentschieden! ")<<cheer(2)<<" "<<face(2)<<endl; dr++; }
		else if((me+2)%3==y){ cout<<"  >>> "<<T("你赢了! ","You win! ","勝ち! ","Du gewinnst! ")<<cheer(0)<<" "<<face(0)<<endl; w++; snd_hit(); }
		else { cout<<"  >>> "<<T("你输了! ","You lose! ","負け! ","Du verlierst! ")<<cheer(1)<<" "<<face(1)<<endl; l++; }
		sleep_ms(600);
	}
	stats.rpsW += w; stats.rpsL += l; stats.rpsD += dr; saveStats();
	cout<<endl<<"=========================================="<<endl<<endl;
	cout<<T("  最终  你 ","  Final  You ","  最終  あなた ","  Gesamt  Du ")<<w<<T("  AI ","  AI ","  AI ","  AI ")<<l<<T("  平局 ","  Draw ","  引き分け ","  Unentschieden ")<<dr<<endl<<endl;
	cout<<"=========================================="<<endl;
	sleep_ms(500);
}

const int GS = 11;
char gb[GS][GS];
bool gold[GS][GS];
int gdx[]={0,1,1,-1};
int gdy[]={1,0,1,1};

void gomoku_init(){
	for(int i=0;i<GS;i++) for(int j=0;j<GS;j++){ gb[i][j]='.'; gold[i][j]=false; }
}
string gcolor(int x,int y){
	if(gold[x][y]) return "\033[1;93m";
	if(gb[x][y]=='X') return "\033[1;96m";
	if(gb[x][y]=='O') return "\033[1;91m";
	return "\033[0m";
}
void gomoku_draw(){
	cout<<endl<<"    ";
	for(int j=0;j<GS;j++) cout<<(char)('A'+j)<<" ";
	cout<<endl<<"    ";
	for(int j=0;j<GS;j++) cout<<"--";
	cout<<endl;
	for(int i=0;i<GS;i++){
		if(i+1<10) cout<<" "<<(i+1)<<"  ";
		else       cout<<(i+1)<<"  ";
		for(int j=0;j<GS;j++) cout<<gcolor(i,j)<<gb[i][j]<<"\033[0m ";
		cout<<endl;
	}
	cout<<endl;
}
int line_len(int x,int y,char c){
	int best=0;
	for(int k=0;k<4;k++){
		int cnt=1;
		for(int s=1;s<=4;s++){
			int nx=x+gdx[k]*s, ny=y+gdy[k]*s;
			if(nx<0||nx>=GS||ny<0||ny>=GS) break;
			if(gb[nx][ny]!=c) break;
			cnt++;
		}
		for(int s=1;s<=4;s++){
			int nx=x-gdx[k]*s, ny=y-gdy[k]*s;
			if(nx<0||nx>=GS||ny<0||ny>=GS) break;
			if(gb[nx][ny]!=c) break;
			cnt++;
		}
		if(cnt>best) best=cnt;
	}
	return best;
}
bool gomoku_win(int x,int y,char c){ return line_len(x,y,c)>=5; }
void mark_gold(int x,int y,char c){
	for(int k=0;k<4;k++){
		vector<pii> line; line.push_back({x,y});
		for(int s=1;s<=4;s++){
			int nx=x+gdx[k]*s, ny=y+gdy[k]*s;
			if(nx<0||nx>=GS||ny<0||ny>=GS) break;
			if(gb[nx][ny]!=c) break;
			line.push_back({nx,ny});
		}
		for(int s=1;s<=4;s++){
			int nx=x-gdx[k]*s, ny=y-gdy[k]*s;
			if(nx<0||nx>=GS||ny<0||ny>=GS) break;
			if(gb[nx][ny]!=c) break;
			line.push_back({nx,ny});
		}
		if((int)line.size()>=5){ for(auto &p:line) gold[p.first][p.second]=true; return; }
	}
}
int gomoku_score(int x,int y,char me,char op){
	int score=0;
	gb[x][y]=me; int a=line_len(x,y,me); gb[x][y]='.';
	if(a>=5)score+=1000000; else if(a==4)score+=10000;
	else if(a==3)score+=500; else if(a==2)score+=50; else score+=1;
	gb[x][y]=op; int b=line_len(x,y,op); gb[x][y]='.';
	if(b>=5)score+=500000; else if(b==4)score+=5000;
	else if(b==3)score+=300; else if(b==2)score+=30;
	return score;
}
pii gomoku_ai(){
	bool empty=true;
	for(int i=0;i<GS;i++) for(int j=0;j<GS;j++) if(gb[i][j]!='.') empty=false;
	if(empty) return {GS/2,GS/2};
	int bx=-1,by=-1,best=-1;
	for(int i=0;i<GS;i++) for(int j=0;j<GS;j++){
		if(gb[i][j]!='.') continue;
		bool near=false;
		for(int di=-2;di<=2&&!near;di++) for(int dj=-2;dj<=2&&!near;dj++){
			int ni=i+di,nj=j+dj;
			if(ni<0||ni>=GS||nj<0||nj>=GS) continue;
			if(gb[ni][nj]!='.') near=true;
		}
		if(!near) continue;
		int s=gomoku_score(i,j,'O','X');
		if(s>best){ best=s; bx=i; by=j; }
	}
	if(bx<0) return {-1,-1};
	return {bx,by};
}
bool is_num_str(string s){
	if(s.empty()) return false;
	for(char c:s) if(c<'0'||c>'9') return false;
	return true;
}
int parse_row(string s){ if(!is_num_str(s)) return -1; return stoi(s)-1; }
int parse_col(string s){
	if(s.size()==1){
		if(s[0]>='A'&&s[0]<='Z') return s[0]-'A';
		if(s[0]>='a'&&s[0]<='z') return s[0]-'a';
	}
	if(is_num_str(s)) return stoi(s)-1;
	return -1;
}
void gomoku(){
	cout<<endl<<"=========================================="<<endl<<endl;
	cout<<"  "<<T("五子棋  (你先手, X=你, O=AI)","Gomoku  (You first, X=You, O=AI)","五目並べ  (先手あなた, X=あなた, O=AI)","Gomoku  (Du zuerst, X=Du, O=AI)")<<endl<<endl;
	cout<<"  "<<T("输入: 行 列 (例如 6 F 或 6 6), q 退出","Input: row col (e.g. 6 F or 6 6), q to quit","入力: 行 列 (例 6 F または 6 6), q で終了","Eingabe: Zeile Spalte (z.B. 6 F oder 6 6), q zum Beenden")<<endl<<endl;

	bool keepPlaying = true;
	while(keepPlaying){
		gomoku_init();
		int moves=0;
		while(1){
			gomoku_draw();
			cout<<T("你的落子 (q退出): ","Your move (q quit): ","あなたの手 (q終了): ","Dein Zug (q beenden): ");
			string a,b;
			if(!(cin>>a)){ cin.clear(); keepPlaying=false; break; }
			if(a=="q"||a=="quit"){ keepPlaying=false; break; }
			if(!(cin>>b)){ cin.clear(); keepPlaying=false; break; }
			int x=parse_row(a), y=parse_col(b);
			if(x<0||y<0||x>=GS||y>=GS){ cout<<endl<<"  "<<T("无效坐标,请重新输入","Invalid coordinate, try again","無効な座標、もう一度","Ungueltige Koordinate, nochmal")<<endl; continue; }
			if(gb[x][y]!='.'){ cout<<endl<<"  "<<T("该位置已被占用","That cell is occupied","そのマスは既に埋まっている","Dieses Feld ist belegt")<<endl; continue; }
			snd_click();
			gb[x][y]='X'; moves++;
			if(gomoku_win(x,y,'X')){
				mark_gold(x,y,'X'); gomoku_draw();
				cout<<"  >>> "<<T("五子连珠,你赢了! ","Five in a row, you win! ","五目達成、勝ち! ","Fuenf in einer Reihe, du gewinnst! ")<<cheer(0)<<" "<<face(0)<<endl;
				unlock("gomoku"); stats.gmW++; saveStats();
				sleep_ms(350); announce(true); break;
			}
			if(moves>=GS*GS){ stats.gmD++; saveStats(); gomoku_draw(); cout<<"  >>> "<<T("棋盘已满,平局! ","Board full, draw! ","盤面満杯、引き分け! ","Brett voll, unentschieden! ")<<face(2)<<endl; sleep_ms(400); break; }
			cout<<endl<<"  "<<T("AI 思考中...","AI thinking...","AI 考え中...","AI denkt...")<<endl;
			sleep_ms(400);
			pii p=gomoku_ai();
			if(p.first<0){ stats.gmD++; saveStats(); gomoku_draw(); cout<<"  >>> "<<T("AI 无处可下,平局!","AI has no move, draw!","AI の手なし、引き分け!","AI hat keinen Zug, unentschieden!")<<endl; sleep_ms(400); break; }
			gb[p.first][p.second]='O'; moves++;
			cout<<"  AI: "<<(p.first+1)<<" "<<(char)('A'+p.second)<<endl;
			sleep_ms(300);
			if(gomoku_win(p.first,p.second,'O')){
				mark_gold(p.first,p.second,'O'); gomoku_draw();
				cout<<"  >>> "<<T("AI 五子连珠,你输了! ","AI got five, you lose! ","AI 五目、負け! ","AI hat fuenf, du verlierst! ")<<cheer(1)<<" "<<face(1)<<endl;
				stats.gmL++; saveStats();
				sleep_ms(350); announce(false); break;
			}
			if(moves>=GS*GS){ stats.gmD++; saveStats(); gomoku_draw(); cout<<"  >>> "<<T("棋盘已满,平局! ","Board full, draw! ","盤面満杯、引き分け! ","Brett voll, unentschieden! ")<<face(2)<<endl; sleep_ms(400); break; }
		}
		if(!keepPlaying) break;
		cout<<endl<<T("再玩一局? (y/n, q退出): ", "Play again? (y/n, q quit): ", "もう一回? (y/n, q終了): ", "Nochmal? (y/n, q beenden): ");
		string c;
		if(!(cin >> c)){ cin.clear(); return; }
		for(auto &ch : c) ch = tolower(ch);
		if(c == "n" || c == "no" || c == "q" || c == "quit" || c == "exit") keepPlaying = false;
	}
}

const int MGW = 15;
const int MGH = 15;
char mz[MGH][MGW];
bool mvis[MGH][MGW];

void maze_dfs(int x, int y){
	mvis[y][x] = true; mz[y][x] = ' ';
	int dirs[4][2] = {{2,0},{-2,0},{0,2},{0,-2}};
	for(int i=3;i>0;i--){ int j = rand() % (i+1); swap(dirs[i][0], dirs[j][0]); swap(dirs[i][1], dirs[j][1]); }
	for(int k=0;k<4;k++){
		int dx = dirs[k][0], dy = dirs[k][1];
		int nx = x + dx, ny = y + dy;
		if(nx > 0 && nx < MGW-1 && ny > 0 && ny < MGH-1 && !mvis[ny][nx]){
			mz[y + dy/2][x + dx/2] = ' ';
			maze_dfs(nx, ny);
		}
	}
}
void maze_init(){
	for(int i=0;i<MGH;i++) for(int j=0;j<MGW;j++){ mz[i][j]='#'; mvis[i][j]=false; }
	maze_dfs(1, 1); mz[1][1] = 'S'; mz[MGH-2][MGW-2] = 'E';
}
void maze_draw(int px, int py, int steps){
	cout << endl << "    ";
	for(int j=0;j<MGW;j++) cout << (char)('A'+j) << ' ';
	cout << endl << "    ";
	for(int j=0;j<MGW;j++) cout << "--";
	cout << endl;
	for(int i=0;i<MGH;i++){
		if(i+1 < 10) cout << ' ' << (i+1) << "  ";
		else cout << (i+1) << "  ";
		for(int j=0;j<MGW;j++){
			if(i==py && j==px) cout << "\033[1;96m@\033[0m ";
			else if(mz[i][j] == '#') cout << "\033[1;90m#\033[0m ";
			else if(mz[i][j] == 'E') cout << "\033[1;93mE\033[0m ";
			else cout << "  ";
		}
		cout << endl;
	}
	cout << endl << "  " << T("步数: ","Steps: ","歩数: ","Schritte: ") << steps << endl;
}
void maze_game(){
	cout << endl << "==========================================" << endl << endl;
	cout << "  " << T("迷宫 — 从 S 走到 E, WASD 移动, q 退出","Maze -- from S to E, WASD to move, q to quit","迷路 — S から E へ, WASD で移動, q で終了","Labyrinth -- von S nach E, WASD zum Bewegen, q zum Beenden") << endl << endl;
	while(1){
		maze_init();
		int px = 1, py = 1, steps = 0;
		while(1){
			maze_draw(px, py, steps);
			if(px == MGW-2 && py == MGH-2){
				cout << "  >>> " << T("你走出了迷宫! ","You escaped the maze! ","迷路を抜けた! ","Du bist entkommen! ") << cheer(0) << " " << face(0) << endl;
				stats.mzW++;
				if(steps <= 30) unlock("maze30");
				saveStats();
				sleep_ms(350); announce(true); break;
			}
			cout << T("移动 (w/a/s/d, q退出): ", "Move (w/a/s/d, q quit): ", "移動 (w/a/s/d, q終了): ", "Bewegen (w/a/s/d, q beenden): ");
			string s;
			if(!(cin >> s)){ cin.clear(); continue; }
			for(auto &ch : s) ch = tolower(ch);
			if(s == "q" || s == "quit" || s == "exit") return;
			int nx = px, ny = py;
			if(s == "w") ny--;
			else if(s == "s") ny++;
			else if(s == "a") nx--;
			else if(s == "d") nx++;
			else continue;
			if(nx < 0 || nx >= MGW || ny < 0 || ny >= MGH) continue;
			if(mz[ny][nx] == '#') continue;
			px = nx; py = ny; steps++;
			snd_click();
		}
		cout << endl << T("再玩一局? (y/n, q退出): ", "Play again? (y/n, q quit): ", "もう一回? (y/n, q終了): ", "Nochmal? (y/n, q beenden): ");
		string c;
		if(!(cin >> c)){ cin.clear(); return; }
		for(auto &ch : c) ch = tolower(ch);
		if(c == "n" || c == "no" || c == "q" || c == "quit" || c == "exit") return;
	}
}

void squid_bar(int pos, int maxpos, string color){
	int width = 20;
	int filled = pos * width / maxpos;
	if(filled > width) filled = width;
	cout << color;
	for(int i=0;i<filled;i++) cout << "=";
	for(int i=filled;i<width;i++) cout << "-";
	cout << "\033[0m " << pos << "/" << maxpos;
}
void squid_game(){
	const int TRACK = 15;
	cout << endl << "==========================================" << endl << endl;
	cout << "  " << T("鱿鱼游戏 — 红灯停, 绿灯行","Squid Game -- Red light, Green light","イカゲーム — 赤信号、青信号","Squid Game -- Rot, Gruen") << endl << endl;
	cout << "  " << T("绿灯: 输入 走 前进. 红灯: 输入 停 安全. 红灯时走 = 出局!","Green: type 'go' to move. Red: type 'stop'. Moving on RED = OUT!","青: 'go' で進む. 赤: 'stop' で安全. 赤で進むと失格!","Gruen: 'go' zum Bewegen. Rot: 'stop'. Bei Rot bewegen = raus!") << endl << endl;
	cout << "  " << T("目标: 先到达 15 步终点. q 退出","Goal: reach 15 first. q to quit","目標: 15 に先に着く. q で終了","Ziel: zuerst 15 erreichen. q zum Beenden") << endl << endl;
	while(1){
		int ppos = 0, apos = 0, turn = 0;
		while(1){
			turn++;
			bool green = (rand() % 100 < 70);
			cout << endl << "==========================================" << endl << endl;
			cout << "  " << T("第 ", "Turn ", "第 ", "Runde ") << turn << T(" 回合", "", " 回", "") << endl << endl;
			if(green) cout << "  \033[1;92m" << T("[绿灯] 可以前进!", "[GREEN] You can move!", "[青] 進め!", "[GRUEN] Vorwaerts!") << "\033[0m" << endl;
			else      cout << "  \033[1;91m" << T("[红灯] 不要动!", "[RED] Don't move!", "[赤] 止まれ!", "[ROT] Stehen bleiben!") << "\033[0m" << endl;
			cout << endl;
			cout << "  " << T("[你] ", "[You] ", "[あなた] ", "[Du] ");
			squid_bar(ppos, TRACK, "\033[1;96m"); cout << endl;
			cout << "  " << T("[AI] ", "[AI] ", "[AI] ", "[AI] ");
			squid_bar(apos, TRACK, "\033[1;91m"); cout << endl << endl;
			cout << T("输入 (走/停, q退出): ", "Input (go/stop, q quit): ", "入力 (go/stop, q終了): ", "Eingabe (go/stop, q beenden): ");
			string s;
			if(!(cin >> s)){ cin.clear(); continue; }
			for(auto &ch : s) ch = tolower(ch);
			if(s == "q" || s == "quit" || s == "exit") return;
			bool pMove = (s == "走" || s == "go" || s == "g" || s == "w");
			bool pStop = (s == "停" || s == "stop" || s == "s");
			if(!pMove && !pStop){ cout << "  " << T("无效输入, 请输入 走 或 停","Invalid input. Type go or stop","無効な入力. go か stop を入力","Ungueltige Eingabe. go oder stop") << endl; turn--; continue; }
			bool aMove = green ? true : (rand() % 100 < 20);
			cout << endl;
			if(green){
				if(pMove){ ppos++; snd_click(); cout << "  " << T("你前进了 1 步", "You moved forward 1 step", "1 歩進んだ", "1 Schritt vorwaerts") << endl; }
				else cout << "  " << T("你选择原地不动", "You stayed still", "その場に留まった", "Du bleibst stehen") << endl;
				if(aMove){ apos++; cout << "  " << T("AI 前进了 1 步", "AI moved forward 1 step", "AI が 1 歩進んだ", "AI 1 Schritt vorwaerts") << endl; }
			} else {
				bool pOut = false, aOut = false;
				if(pMove){ cout << "  \033[1;91m" << T("你在红灯时动了! 出局!", "You moved on RED! OUT!", "赤で動いた! 失格!", "Bei ROT bewegt! RAUS!") << "\033[0m" << endl; pOut = true; }
				else cout << "  " << T("你安全", "You're safe", "セーフ", "Du bist sicher") << endl;
				if(aMove){ cout << "  \033[1;92m" << T("AI 在红灯时动了! AI 出局!", "AI moved on RED! AI out!", "AI が赤で動いた! AI 失格!", "AI bei ROT bewegt! AI raus!") << "\033[0m" << endl; aOut = true; }
				else cout << "  " << T("AI 安全", "AI is safe", "AI セーフ", "AI ist sicher") << endl;
				if(pOut || aOut){
					sleep_ms(400);
					if(pOut && aOut){ cout << "  >>> " << T("双方出局, 平局!", "Both out, draw!", "両者失格、引き分け!", "Beide raus, unentschieden!") << endl; sleep_ms(400); }
					else if(pOut){ cout << "  >>> " << T("你输了!", "You lose!", "負け!", "Du verlierst!") << " " << cheer(1) << " " << face(1) << endl; stats.sqL++; saveStats(); sleep_ms(350); announce(false); }
					else { cout << "  >>> " << T("你赢了!", "You win!", "勝ち!", "Du gewinnst!") << " " << cheer(0) << " " << face(0) << endl; stats.sqW++; saveStats(); sleep_ms(350); announce(true); }
					break;
				}
			}
			if(ppos >= TRACK){ cout << endl << "  >>> " << T("你到达终点! 你赢了!", "You reached the end! You win!", "ゴール! 勝ち!", "Ziel erreicht! Du gewinnst!") << " " << cheer(0) << " " << face(0) << endl; stats.sqW++; saveStats(); sleep_ms(350); announce(true); break; }
			if(apos >= TRACK){ cout << endl << "  >>> " << T("AI 到达终点! 你输了!", "AI reached the end! You lose!", "AI がゴール! 負け!", "AI am Ziel! Du verlierst!") << " " << cheer(1) << " " << face(1) << endl; stats.sqL++; saveStats(); sleep_ms(350); announce(false); break; }
			sleep_ms(300);
		}
		cout << endl << T("再玩一局? (y/n, q退出): ", "Play again? (y/n, q quit): ", "もう一回? (y/n, q終了): ", "Nochmal? (y/n, q beenden): ");
		string c;
		if(!(cin >> c)){ cin.clear(); return; }
		for(auto &ch : c) ch = tolower(ch);
		if(c == "n" || c == "no" || c == "q" || c == "quit" || c == "exit") return;
	}
}

/*==================================================
            骗 子 酒 馆
==================================================*/
enum { LB_J=0, LB_Q=1, LB_K=2, LB_JOKER=3, LB_DEVIL_Q=4 };

string lbCardName(int c){
	if(c==LB_J) return "J";
	if(c==LB_Q) return "Q";
	if(c==LB_K) return "K";
	if(c==LB_JOKER) return "JOKER";
	return T("魔鬼Q","DevilQ","デビルQ","TeufelQ");
}
string lbCardColor(int c){
	if(c==LB_JOKER)   return "\033[1;95m";
	if(c==LB_DEVIL_Q) return "\033[1;91m";
	if(c==LB_J)       return "\033[1;94m";
	if(c==LB_Q)       return "\033[1;92m";
	if(c==LB_K)       return "\033[1;93m";
	return "\033[0m";
}
string lbTargetName(int t){
	if(t==LB_J) return "J";
	if(t==LB_Q) return "Q";
	return "K";
}
bool lbIsMatch(int card, int target){
	if(card == LB_JOKER) return true;
	if(card == LB_DEVIL_Q) return target == LB_Q;
	return card == target;
}
int lbDrawCard(){
	int r = rand() % 22;
	if(r < 6) return LB_J;
	if(r < 12) return LB_Q;
	if(r < 18) return LB_K;
	if(r < 20) return LB_JOKER;
	return LB_DEVIL_Q;
}

void liars_bar(){
	cout << endl << "==========================================" << endl << endl;
	cout << "  \033[1;95m" << T("骗 子 酒 馆","LIAR'S BAR","ライアーズバー","LUEGNERBAR") << "\033[0m" << endl << endl;

	cout << "  " << T("请选择模式:","Choose mode:","モード選択:","Modus waehlen:") << endl << endl;
	cout << "    1. " << T("正常模式 (你 vs 1 AI)","Normal (You vs 1 AI)","ノーマル (あなた vs 1 AI)","Normal (Du vs 1 KI)") << endl;
	cout << "    2. " << T("多人模式 (你 vs 3 AI)","Multiplayer (You vs 3 AI)","マルチ (あなた vs 3 AI)","Multiplayer (Du vs 3 KI)") << endl;
	cout << "    0. " << T("返回","Back","戻る","Zurueck") << endl << endl;
	cout << "  " << T("请输入: ","> ","入力: ","Eingabe: ");

	int mode;
	if(!(cin >> mode)){ cin.clear(); string tmp; cin >> tmp; return; }
	if(mode != 1 && mode != 2) return;

	int nPlayers = (mode == 1) ? 2 : 4;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<int> hp(nPlayers, 3);
	vector<string> names(nPlayers);
	names[0] = T("你","You","あなた","Du");
	for(int i=1;i<nPlayers;i++) names[i] = "AI" + to_string(i);

	cout << endl << "  \033[1;93m" << T("规则速览:","Rules:","ルール:","Regeln:") << "\033[0m" << endl;
	cout << "  " << T("- 每人 3 命, 每轮 5 张手牌","- 3 lives, 5 cards per round","- 3 ライフ、毎回 5 枚","- 3 Leben, 5 Karten pro Runde") << endl;
	cout << "  " << T("- 每轮随机目标: J / Q / K","- Random target: J / Q / K","- 毎回ランダム: J / Q / K","- Zufaelliges Ziel: J / Q / K") << endl;
	cout << "  " << T("- 一次可出 1-3 张牌 (如 1 3 / 13 / 1,3)","- Play 1-3 cards (1 3 / 13 / 1,3)","- 1-3 枚 (1 3 / 13 / 1,3)","- 1-3 Karten (1 3 / 13 / 1,3)") << endl;
	cout << "  " << T("- JOKER 是万能牌, 永远算真","- JOKER is wild, always counts","- JOKER は万能、常に真","- JOKER wild, immer wahr") << endl;
	cout << "  " << T("- 魔鬼Q 只能当 Q, 翻开时质疑者 -2 命!","- DevilQ only as Q, if revealed doubter -2!","- デビルQ は Q のみ、開いたら疑った方 -2!","- TeufelQ nur als Q, aufgedeckt Zweifler -2!") << endl;
	cout << "  " << T("- 质疑翻开整叠: 有假 → 出牌者扣假牌数, 全真 → 质疑者 -1","- Reveal stack: any lie -> player -lies, all true -> doubter -1","- 全開: 嘘→出した方-嘘数、真→疑った方-1","- Aufdecken: Luege -> Spieler -Luegen, echt -> Zweifler -1") << endl;
	cout << "  " << T("- 命归零淘汰, 最后一人胜","- Lose all lives = out, last wins","- ライフ 0 で脱落、最後が勝ち","- Alle Leben weg = raus, Letzter gewinnt") << endl << endl;
	cout << "  " << T("按回车开始...","Press Enter to start...","Enter で開始...","Enter zum Starten...") << endl;
	{ string dummy; getline(cin, dummy); }

	while(true){
		int aliveCount = 0;
		for(int i=0;i<nPlayers;i++) if(hp[i] > 0) aliveCount++;
		if(aliveCount <= 1) break;
		if(hp[0] <= 0) break;

		vector<vector<int>> hands(nPlayers);
		for(int i=0;i<nPlayers;i++){
			if(hp[i] <= 0) continue;
			for(int j=0;j<5;j++) hands[i].push_back(lbDrawCard());
		}
		int target = rand() % 3;

		cout << endl << "========== " << T("新一轮","New Round","新ラウンド","Neue Runde") << " ==========" << endl;
		cout << "  " << T("目标牌","Target","目標","Ziel") << ": "
		     << lbCardColor(target == LB_J ? LB_J : (target == LB_Q ? LB_Q : LB_K))
		     << "[" << lbTargetName(target) << "]\033[0m" << endl;
		cout << "  " << T("存活:","Alive:","生存:","Am Leben:") << " ";
		for(int i=0;i<nPlayers;i++){ if(hp[i] > 0) cout << names[i] << "(" << hp[i] << ") "; }
		cout << endl;

		vector<int> lastStack;
		int lastPlayer = -1;
		int cur = 0;
		while(hp[cur] <= 0) cur = (cur+1) % nPlayers;
		bool roundEnd = false;

		while(!roundEnd){
			if(cur == 0){
				// ===== 玩家回合 =====
				cout << endl << "  " << T("你的手牌","Your hand","手札","Hand") << ": ";
				for(int i=0;i<(int)hands[0].size();i++){
					cout << "[" << (i+1) << "]" << lbCardColor(hands[0][i]) << lbCardName(hands[0][i]) << "\033[0m ";
				}
				cout << endl;

				if(lastPlayer >= 1){
					cout << "  " << T("上家: ","Last: ","前: ","Letzter: ") << names[lastPlayer]
					     << " " << T("声明出了 ","claimed ","宣言 ","behauptet ")
					     << lastStack.size() << " " << T("张是","cards of","枚の","Karten") << " " << lbTargetName(target) << endl;
					cout << "  " << T("操作: 数字序列=出牌(如 1 3 / 13, 最多3张), d=质疑上家, q=退出",
					                   "Controls: N...=play (1 3 / 13, up to 3), d=doubt, q=quit",
					                   "操作: 数字=出す (1 3 / 13, 最大3), d=疑う, q=終了",
					                   "Steuerung: N=spielen (1 3 / 13, max 3), d=zweifeln, q=quit") << endl;
				} else {
					cout << "  " << T("操作: 数字序列=出牌(如 1 3 / 13, 最多3张), q=退出",
					                   "Controls: N...=play (1 3 / 13, up to 3), q=quit",
					                   "操作: 数字=出す (1 3 / 13, 最大3), q=終了",
					                   "Steuerung: N=spielen (1 3 / 13, max 3), q=quit") << endl;
				}
				cout << "> ";

				string raw;
				if(!getline(cin, raw)){ cin.clear(); break; }
				string cmd;
				for(char c : raw){
					if(c == ' ' || c == ',' || c == '\t') continue;
					cmd += tolower(c);
				}

				if(cmd == "q" || cmd == "quit" || cmd == "exit"){
					cout << endl << "  " << T("已退出对局","Quit","終了","Beendet") << endl;
					return;
				}

				if((cmd == "d" || cmd == "doubt") && lastPlayer >= 1){
					snd_click();
					cout << endl << "  \033[1;95m>>> " << T("你质疑 ","You doubt ","疑う ","Du zweifelst ") << names[lastPlayer] << "\033[0m" << endl;
					sleep_ms(400);
					cout << "  " << names[lastPlayer] << " " << T("出的整叠:","played:","出した:","spielte:") << " ";
					for(int c : lastStack) cout << lbCardColor(c) << lbCardName(c) << "\033[0m ";
					cout << endl;
					sleep_ms(300);

					bool hasDevil = false;
					int lieCount = 0;
					for(int c : lastStack){
						if(c == LB_DEVIL_Q && target == LB_Q) hasDevil = true;
						if(!lbIsMatch(c, target)) lieCount++;
					}

					if(hasDevil){
						cout << "  \033[1;91m>>> " << T("魔鬼Q 生效! 你扣 2 命!","DevilQ triggers! You -2 lives!","デビルQ 発動! あなた -2 ライフ!","TeufelQ aktiv! Du -2 Leben!") << "\033[0m" << endl;
						hp[0] -= 2;
						snd_lose();
						unlock("devil");
					} else if(lieCount == 0){
						cout << "  \033[1;91m>>> " << T("全是真的... 你扣 1 命","All true... You -1","全部本当... あなた -1","Alles wahr... Du -1") << "\033[0m" << endl;
						hp[0] -= 1;
						snd_lose();
					} else {
						cout << "  \033[1;92m>>> " << T("找到 ","Found ","見つけた ","Gefunden ") << lieCount
						     << T(" 张假牌! 他扣 "," lies! He -"," 枚の嘘! 彼 -"," Luegen! Er -")
						     << lieCount << T(" 命"," lives"," ライフ"," Leben") << "\033[0m" << endl;
						hp[lastPlayer] -= lieCount;
						snd_win();
						unlock("bluff");
					}
					roundEnd = true;
				} else {
					bool isNum = !cmd.empty();
					for(char c : cmd) if(!isdigit(c)){ isNum = false; break; }
					if(!isNum){ cout << "  " << T("无效输入","Invalid input","無効","Ungueltig") << endl; continue; }
					if((int)cmd.size() > 3){ cout << "  " << T("最多出 3 张","Up to 3 cards","最大 3 枚","Max 3 Karten") << endl; continue; }

					vector<int> idxs;
					bool ok = true;
					set<int> seen;
					for(char c : cmd){
						int idx = c - '1';
						if(idx < 0 || idx >= (int)hands[0].size()){ ok = false; break; }
						if(seen.count(idx)){ ok = false; break; }
						seen.insert(idx);
						idxs.push_back(idx);
					}
					if(!ok || idxs.empty()){ cout << "  " << T("无效编号","Invalid index","無効","Ungueltig") << endl; continue; }

					sort(idxs.begin(), idxs.end(), greater<int>());
					lastStack.clear();
					for(int idx : idxs){
						lastStack.push_back(hands[0][idx]);
						hands[0].erase(hands[0].begin() + idx);
					}
					lastPlayer = 0;
					snd_click();
					cout << "  \033[1;96m>>> " << T("你出了 ","You played ","出した: ","Du spielst ") << lastStack.size() << " " << T("张牌, 声明是 ","cards, claiming ","枚、宣言: ","Karten, behauptest ") << lbTargetName(target) << "\033[0m" << endl;
					if(hands[0].empty()){
						cout << "  " << T("手牌出尽, 无人受罚, 重开一轮","Hand empty, no penalty, restart","手札切れ、ペナルティなし、再開","Hand leer, keine Strafe, neue Runde") << endl;
						roundEnd = true;
					} else {
						cur = (cur + 1) % nPlayers;
						while(hp[cur] <= 0) cur = (cur + 1) % nPlayers;
					}
				}
			} else {
				// ===== AI 回合 =====
				sleep_ms(400);

				bool canDoubt = (lastPlayer >= 0 && lastPlayer != cur);
				int myMatchCount = 0;
				for(int c : hands[cur]) if(lbIsMatch(c, target)) myMatchCount++;
				bool hasDevil = false;
				for(int c : hands[cur]) if(c == LB_DEVIL_Q) hasDevil = true;

				int doubtChance = 0;
				if(canDoubt){
					doubtChance = 12 + myMatchCount * 8 + difficulty * 3;
					if(myMatchCount == 0) doubtChance += 15;
					doubtChance += (int)lastStack.size() * 6;
					if(hasDevil) doubtChance -= 10;
					if(doubtChance < 5) doubtChance = 5;
					if(doubtChance > 85) doubtChance = 85;
				}

				int r = rand() % 100;
				if(canDoubt && r < doubtChance){
					cout << endl << "  \033[1;95m>>> " << names[cur] << " " << T("质疑 ","doubts ","が疑う ","zweifelt ") << names[lastPlayer] << "\033[0m" << endl;
					sleep_ms(400);
					cout << "  " << names[lastPlayer] << " " << T("出的整叠:","played:","出した:","spielte:") << " ";
					for(int c : lastStack) cout << lbCardColor(c) << lbCardName(c) << "\033[0m ";
					cout << endl;
					sleep_ms(300);

					bool hasDevilCard = false;
					int lieCount = 0;
					for(int c : lastStack){
						if(c == LB_DEVIL_Q && target == LB_Q) hasDevilCard = true;
						if(!lbIsMatch(c, target)) lieCount++;
					}

					if(hasDevilCard){
						cout << "  \033[1;91m>>> " << T("魔鬼Q 生效! 质疑者扣 2 命!","DevilQ triggers! Doubter -2!","デビルQ 発動! 疑った方 -2!","TeufelQ aktiv! Zweifler -2!") << "\033[0m" << endl;
						hp[cur] -= 2;
					} else if(lieCount == 0){
						cout << "  \033[1;91m>>> " << T("全是真的, 质疑者 -1","All true, doubter -1","全部本当、疑った方 -1","Alles wahr, Zweifler -1") << "\033[0m" << endl;
						hp[cur] -= 1;
					} else {
						cout << "  \033[1;92m>>> " << T("找到 ","Found ","見つけた ","Gefunden ") << lieCount
						     << T(" 张假牌! 出牌者扣 "," lies! Player -"," 枚の嘘! 出した方 -"," Luegen! Spieler -")
						     << lieCount << T(" 命"," lives"," ライフ"," Leben") << "\033[0m" << endl;
						hp[lastPlayer] -= lieCount;
					}
					roundEnd = true;
				} else {
					// ================================================================
					// ========== AI 出牌决策（彻底重写，清晰、健壮、有策略）==========
					// ================================================================
					int totalCards = (int)hands[cur].size();

					// --- 第 1 步：分类手牌 ---
					vector<int> trueIdx;      // 算真的牌的下标（含 JOKER、目标 Q 时的魔鬼Q）
					vector<int> falseIdx;     // 算假的牌的下标
					vector<int> jokerIdx;     // JOKER 的位置（要保留，不轻易出）
					vector<int> devilIdx;     // 魔鬼Q 的位置
					vector<int> normalTrue;   // 普通真牌（不含 JOKER、魔鬼Q）
					vector<int> normalFalse;  // 普通假牌（不含魔鬼Q）
					vector<int> devilAsFalse; // 目标非 Q 时的魔鬼Q（纯废牌，优先清掉）

					for(int i = 0; i < totalCards; i++){
						int c = hands[cur][i];
						if(c == LB_JOKER){
							jokerIdx.push_back(i);
							trueIdx.push_back(i);
						} else if(c == LB_DEVIL_Q){
							devilIdx.push_back(i);
							if(target == LB_Q){
								trueIdx.push_back(i);
							} else {
								falseIdx.push_back(i);
								devilAsFalse.push_back(i);
							}
						} else if(c == target){
							trueIdx.push_back(i);
							normalTrue.push_back(i);
						} else {
							falseIdx.push_back(i);
							normalFalse.push_back(i);
						}
					}

					// --- 第 2 步：决定出几张（1~3，手牌少时尽量多出） ---
					int playCount;
					if(totalCards <= 1){
						playCount = totalCards;
					} else if(totalCards == 2){
						playCount = 2;                    // 手牌少，尽量清空
					} else if(totalCards == 3){
						playCount = 1 + rand() % 3;       // 1~3
					} else {
						playCount = 1 + rand() % 2;       // 4~5 张时保守
					}
					// 高难度 AI 更激进，快速清空手牌
					if(difficulty >= 3 && totalCards <= 3){
						playCount = totalCards;
					}
					// 夹紧到 [1, 3]
					if(playCount < 1) playCount = 1;
					if(playCount > 3) playCount = 3;
					if(playCount > totalCards) playCount = totalCards;
					if(playCount < 1) playCount = 1;

					int trueCount = (int)trueIdx.size();

					// --- 第 3 步：选牌 ---
					vector<int> chosenIdx;
					vector<bool> picked(totalCards, false);
					auto tryPick = [&](int idx) -> bool {
						if(idx < 0 || idx >= totalCards) return false;
						if(picked[idx]) return false;
						if((int)chosenIdx.size() >= playCount) return false;
						picked[idx] = true;
						chosenIdx.push_back(idx);
						return true;
					};

					if(trueCount >= playCount){
						// ===== 情况 A：真牌够用，尽量出真（保留 JOKER 和魔鬼Q） =====
						// 先出普通真牌
						for(int idx : normalTrue){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
						// 普通真牌不够，考虑出 JOKER（仅当手牌 <= 2 时，否则保留）
						if((int)chosenIdx.size() < playCount && totalCards <= 2){
							for(int idx : jokerIdx){
								if((int)chosenIdx.size() >= playCount) break;
								tryPick(idx);
							}
						}
						// 还不够，出目标 Q 的魔鬼Q（它是真的）
						if((int)chosenIdx.size() < playCount && target == LB_Q){
							for(int idx : devilIdx){
								if((int)chosenIdx.size() >= playCount) break;
								tryPick(idx);
							}
						}
						// 兜底：用剩余的任意真牌补
						if((int)chosenIdx.size() < playCount){
							for(int idx : trueIdx){
								if((int)chosenIdx.size() >= playCount) break;
								tryPick(idx);
							}
						}
					} else if(trueCount > 0){
						// ===== 情况 B：有真有假，混出（先用真牌打底，再用假牌凑） =====
						// 先出一张普通真牌打底
						if(!normalTrue.empty()){
							int pick = normalTrue[rand() % normalTrue.size()];
							tryPick(pick);
						} else if(target == LB_Q && !devilIdx.empty()){
							// 目标 Q 且有魔鬼Q，可当炸弹出（被质疑时对方 -2）
							tryPick(devilIdx[0]);
						} else if(!jokerIdx.empty() && totalCards <= 2){
							// 手牌少时用 JOKER 补
							tryPick(jokerIdx[0]);
						} else {
							// 随便出一张真牌（可能就是魔鬼Q 当 Q）
							for(int idx : trueIdx){
								if((int)chosenIdx.size() >= playCount) break;
								tryPick(idx);
							}
						}
						// 用假牌凑数：优先清掉非 Q 目标的魔鬼Q（纯废牌）
						for(int idx : devilAsFalse){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
						for(int idx : normalFalse){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
						for(int idx : falseIdx){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
					} else {
						// ===== 情况 C：全假，必须撒谎，优先清掉废牌 =====
						for(int idx : devilAsFalse){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
						for(int idx : normalFalse){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
						for(int idx : falseIdx){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(idx);
						}
					}

					// --- 兜底：还没选够，随便补（不应该发生，但保底） ---
					if((int)chosenIdx.size() < playCount){
						for(int i = 0; i < totalCards; i++){
							if((int)chosenIdx.size() >= playCount) break;
							tryPick(i);
						}
					}
					if(chosenIdx.empty()) chosenIdx.push_back(0);
					if((int)chosenIdx.size() > playCount) chosenIdx.resize(playCount);
					if(chosenIdx.empty()) chosenIdx.push_back(0);

					// --- 执行出牌：从大到小删除，避免索引移位 ---
					sort(chosenIdx.begin(), chosenIdx.end(), greater<int>());
					lastStack.clear();
					for(int idx : chosenIdx){
						if(idx < 0 || idx >= (int)hands[cur].size()) continue;
						lastStack.push_back(hands[cur][idx]);
						hands[cur].erase(hands[cur].begin() + idx);
					}

					lastPlayer = cur;
					snd_click();
					cout << "  \033[1;91m>>> " << names[cur] << " " << T("出了 ","played ","出した: ","spielte ") << lastStack.size() << " " << T("张牌, 声明是 ","cards, claiming ","枚、宣言: ","Karten, behauptest ") << lbTargetName(target) << "\033[0m" << endl;
					if(hands[cur].empty()){
						cout << "  " << names[cur] << " " << T("手牌出尽, 重开一轮","hand empty, restart","手札切れ、再開","Hand leer, neue Runde") << endl;
						roundEnd = true;
					} else {
						cur = (cur + 1) % nPlayers;
						while(hp[cur] <= 0) cur = (cur + 1) % nPlayers;
					}
				}
			}
		}

		cout << endl << "  " << T("当前命数:","Lives:","ライフ:","Leben:") << " ";
		for(int i=0;i<nPlayers;i++){
			if(hp[i] > 0) cout << names[i] << "(" << hp[i] << ") ";
			else cout << "\033[1;90m" << names[i] << "(X)\033[0m ";
		}
		cout << endl;
		sleep_ms(600);
	}

	cout << endl << "========== " << T("游戏结束","Game Over","ゲームオーバー","Spiel vorbei") << " ==========" << endl;
	if(hp[0] <= 0){
		cout << "  >>> " << T("你被淘汰了!","You're out!","脱落!","Du bist raus!") << " " << cheer(1) << " " << face(1) << endl;
		stats.lbL++; saveStats();
		sleep_ms(350); announce(false);
	} else {
		cout << "  >>> " << T("你活到最后, 你赢了!","Last one standing, you win!","最後の一人、勝ち!","Letzter ueberlebt, du gewinnst!") << " " << cheer(0) << " " << face(0) << endl;
		stats.lbW++; saveStats();
		sleep_ms(350); announce(true);
	}
}

signed main(){
	too["w"]=1; too["a"]=2; too["s"]=4; too["d"]=3; too["z"]=5;
	too["8"]=6; too["4"]=7; too["5"]=8; too["6"]=9; too["2"]=10;
	too["71"]=11; too["93"]=12; too["f"]=13; too["4466"]=14;
	too["55"]=15; too["46"]=16; too["82"]=17; too["ff"]=18;
	too["7913"]=19; too["456"]=20; too["852"]=21; too["79"]=22; too["13"]=23;
	too["j"]=24; too["jj"]=25;
	srand(time(0));

	loadLearn("ai_memory.txt");
	loadStats();

	intro();

	cout<<"=========================================="<<endl<<endl;
	cout<<"  欢迎来到休闲小游戏"<<endl;
	cout<<"  Welcome to the casual game"<<endl;
	cout<<"  カジュアルゲームへようこそ"<<endl;
	cout<<"  Willkommen beim Gelegenheitsspiel"<<endl<<endl;
	cout<<"=========================================="<<endl<<endl;
	cout<<"  请选择语言 / Choose language / 言語選択 / Sprache waehlen:"<<endl<<endl;
	cout<<"    1. 中文"<<endl<<"    2. English"<<endl<<"    3. 日本語"<<endl<<"    4. Deutsch"<<endl<<endl;
	cout<<"  请输入 / input: ";

	int ls=1;
	if(!(cin>>ls)){ cin.clear(); string tmp; cin>>tmp; ls=1; }
	if(ls==1)lang=0; else if(ls==2)lang=1; else if(ls==3)lang=2; else if(ls==4)lang=3; else lang=1;

	cout<<endl<<"  "<<T("(让我们说中文)","(Let's speak English)","(日本語でいこう)","(Sprechen wir Deutsch)")<<endl;
	sleep_ms(400);

	while(1){
		cout<<endl<<"=========================================="<<endl<<endl;
		cout<<"  "<<T("请选择游戏:","Please choose a game:","ゲームを選んでください:","Waehle ein Spiel:")<<endl<<endl;
		cout<<"    1. "<<T("拍手","Hand Slap","拍手ゲーム","Klatsch-Spiel")<<endl;
		cout<<"    2. "<<T("石头剪刀布","Rock Paper Scissors","じゃんけん","Schere Stein Papier")<<endl;
		cout<<"    3. "<<T("五子棋","Gomoku","五目並べ","Gomoku")<<endl;
		cout<<"    4. "<<T("迷宫","Maze","迷路","Labyrinth")<<endl;
		cout<<"    5. "<<T("鱿鱼游戏","Squid Game","イカゲーム","Squid Game")<<endl;
		cout<<"    6. "<<T("骗子酒馆","Liar's Bar","ライアーズバー","Luegnerbar")<<endl;
		cout<<"    7. "<<T("战绩记录","Scoreboard","戦績","Punkte")<<endl;
		cout<<"    8. "<<T("设置","Settings","設定","Einstellungen")<<endl;
		cout<<"    9. "<<T("静音: ","Mute: ","ミュート: ","Stumm: ")
		    <<(muted ? T("\033[1;91m开\033[0m","\033[1;91mON\033[0m","\033[1;91mON\033[0m","\033[1;91mAN\033[0m")
		             : T("\033[1;92m关\033[0m","\033[1;92mOFF\033[0m","\033[1;92mOFF\033[0m","\033[1;92mAUS\033[0m"))<<endl;
		cout<<"    0. "<<T("退出","Quit","終了","Beenden")<<endl<<endl;
		cout<<"  "<<T("请输入: ","> ","入力: ","Eingabe: ");
		int game;
		if(!(cin>>game)){
			cin.clear(); string tmp; cin>>tmp;
			if(tmp=="q"||tmp=="quit"||tmp=="exit") break;
			cout<<endl<<"  "<<T("无效输入,请输入数字","Invalid input, please enter a number","無効な入力、数字を入力してください","Ungueltige Eingabe, bitte Zahl eingeben")<<endl;
			continue;
		}
		if(game==0) break;
		if(game==7){ showBoard(); continue; }

		if(game==9){
			muted = !muted;
			saveStats();
			cout<<endl<<"  "<<(muted ? T("\033[1;91m已静音\033[0m","\033[1;91mMuted\033[0m","\033[1;91mミュート中\033[0m","\033[1;91mStumm\033[0m")
			                    : T("\033[1;92m已开启声音\033[0m","\033[1;92mSound ON\033[0m","\033[1;92mサウンドON\033[0m","\033[1;92mTon an\033[0m"))<<endl;
			continue;
		}

		if(game==8){
			while(1){
				cout<<endl<<"=========================================="<<endl<<endl;
				cout<<"  \033[1;95m"<<T("设 置","S E T T I N G S","設 定","E I N S T E L L U N G E N")<<"\033[0m"<<endl<<endl;
				cout<<"  "<<T("当前状态:","Current:","現在:","Aktuell:")<<endl;
				cout<<"    "<<T("沉浸式模式: ","Immersive: ","没入: ","Immersiv: ")<<(immersive ? T("开","ON","ON","AN") : T("关","OFF","OFF","AUS"))<<endl;
				cout<<"    "<<T("速度: ","Speed: ","速度: ","Tempo: ")<<(gameSpeed==0 ? T("快","Fast","速い","Schnell") : gameSpeed==1 ? T("中","Medium","普通","Mittel") : T("慢","Slow","遅い","Langsam"))<<endl;
				cout<<"    "<<T("声音: ","Sound: ","サウンド: ","Ton: ")<<(muted ? T("静音","Muted","ミュート","Stumm") : T("开启","ON","ON","AN"))<<endl;
				cout<<"    "<<T("动画效果: ","Animation: ","アニメ: ","Animation: ")<<(enableAnim ? T("开","ON","ON","AN") : T("关","OFF","OFF","AUS"))<<endl;
				cout<<"    "<<T("拍手默认难度: ","Default HS difficulty: ","拍手デフォ難易度: ","HS-Standard: ")<<defaultDifficulty<<endl;
				cout<<endl;
				cout<<"    1. "<<T("切换沉浸式模式","Toggle immersive","没入モード切替","Immersiv umschalten")<<endl;
				cout<<"    2. "<<T("切换速度","Cycle speed","速度切替","Geschwindigkeit wechseln")<<endl;
				cout<<"    3. "<<T("切换静音","Toggle mute","ミュート切替","Stumm umschalten")<<endl;
				cout<<"    4. "<<T("切换动画效果","Toggle animation","アニメ切替","Animation umschalten")<<endl;
				cout<<"    5. "<<T("设置拍手默认难度","Set default HS difficulty","拍手デフォ難易度設定","HS-Standard setzen")<<endl;
				cout<<"    6. "<<T("重置存档","Reset saves","セーブリセット","Speicherstand loeschen")<<endl;
				cout<<"    0. "<<T("返回主菜单","Back to menu","メニューへ","Zurueck zum Menue")<<endl<<endl;
				cout<<"  "<<T("请输入: ","> ","入力: ","Eingabe: ");
				int sub;
				if(!(cin>>sub)){ cin.clear(); string tmp; cin >> tmp; continue; }
				if(sub==0) break;
				if(sub==1){ immersive = !immersive; cout<<endl<<"  "<<T("沉浸式模式: ","Immersive: ","没入: ","Immersiv: ")<<(immersive ? T("开","ON","ON","AN") : T("关","OFF","OFF","AUS"))<<endl; saveStats(); }
				else if(sub==2){ gameSpeed = (gameSpeed+1)%3; cout<<endl<<"  "<<T("速度: ","Speed: ","速度: ","Tempo: ")<<gameSpeed<<endl; saveStats(); }
				else if(sub==3){ muted = !muted; cout<<endl<<"  "<<(muted ? T("已静音","Muted","ミュート中","Stumm") : T("已开启声音","Sound on","サウンドON","Ton an"))<<endl; saveStats(); }
				else if(sub==4){ enableAnim = !enableAnim; cout<<endl<<"  "<<T("动画效果: ","Animation: ","アニメ: ","Animation: ")<<(enableAnim ? T("开","ON","ON","AN") : T("关","OFF","OFF","AUS"))<<endl; saveStats(); }
				else if(sub==5){
					cout<<endl<<"  "<<T("选择默认难度 (1-5): ","Choose default difficulty (1-5): ","デフォ難易度 (1-5): ","Standard (1-5): ");
					int dd;
					if(!(cin>>dd)){ cin.clear(); dd = defaultDifficulty; }
					if(dd < 1 || dd > 5) dd = 2;
					defaultDifficulty = dd;
					cout<<"  "<<T("已设置: ","Set to: ","設定: ","Gesetzt: ")<<defaultDifficulty<<endl;
					saveStats();
				}
				else if(sub==6){
					cout<<endl<<"  \033[1;91m"<<T("警告: 此操作将删除所有战绩、成就和教程进度!","WARNING: This deletes all stats, achievements and tutorial progress!","警告: 全ての戦績?実績?チュートリアルを消します!","WARNUNG: Loescht alle Statistiken, Erfolge und Tutorial-Fortschritte!")<<"\033[0m"<<endl;
					cout<<"  "<<T("确认重置? 输入 YES 确认, 其他取消: ","Confirm reset? Type YES, other cancels: ","リセットする? YES で確定、他でキャンセル: ","Zuruecksetzen? YES bestaetigen, sonst abbrechen: ");
					string cf; if(!(cin>>cf)){ cin.clear(); continue; }
					if(cf == "YES" || cf == "yes"){
						stats = Stats(); ach.clear(); achOrder.clear();
						muted = false; enableAnim = true; defaultDifficulty = 2; immersive = true; gameSpeed = 1;
						saveStats();
						cout<<endl<<"  \033[1;92m"<<T("已重置所有存档","All saves reset","セーブをリセットしました","Speicherstand zurueckgesetzt")<<"\033[0m"<<endl;
						sleep_ms(800);
					} else {
						cout<<"  "<<T("已取消","Cancelled","キャンセル","Abgebrochen")<<endl;
					}
				}
			}
			continue;
		}

		if(game==1){
			tutorial(1);
			cout<<endl<<"=========================================="<<endl<<endl;
			cout<<"  "<<T("请选择难度:","Choose difficulty:","難易度:","Schwierigkeit:")<<endl<<endl;
			cout<<"    1. "<<T("简单 (纯随机)","Easy (random)","かんたん (ランダム)","Einfach (zufaellig)")<<endl;
			cout<<"    2. "<<T("普通 (学习型)","Normal (learning)","ふつう (学習型)","Normal (lernend)")<<endl;
			cout<<"    3. "<<T("困难 (学习+强反制)","Hard (learning + counter)","むずかしい (学習+反撃)","Schwer (lernen + kontern)")<<endl;
			cout<<"    4. "<<T("地狱 (期望DP)","Hell (Expectimax DP)","ヘル (期待値DP)","Hoelle (Erwartungs-DP)")<<endl;
			cout<<"    5. "<<T("超级无敌雷霆恶魔版 (未知先卜)","SUPER DEMON (Foresight)","スーパーデーモン (未来視)","SUPERDAEMON (Vorhersehen)")<<endl<<endl;
			cout<<"  "<<T("请输入 (默认 ","Enter (default ","入力 (デフォルト ","Eingabe (Standard ")<<defaultDifficulty<<"): ";
			if(!(cin>>difficulty)){ cin.clear(); difficulty=defaultDifficulty; }
			if(difficulty<1 || difficulty>5) difficulty=defaultDifficulty;

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout<<endl<<"  "<<T("是否开启沉浸式体验模式? (y/n, 回车默认开启): ","Enable immersive mode? (y/n, Enter=on): ","没入モードを有効? (y/n, Enter で有効): ","Immersiven Modus? (y/n, Enter=an): ");
			string im;
			getline(cin, im);
			for(auto &ch : im) ch = tolower(ch);
			if(im=="n"||im=="no"||im=="off"||im=="0") immersive = false;
			else immersive = true;

			cout<<"  \033[1;96m"<<T("沉浸式模式: ","Immersive: ","没入: ","Immersiv: ")<<(immersive ? T("开启","ON","ON","AN") : T("关闭","OFF","OFF","AUS"))<<"\033[0m"<<endl;

			if(immersive){
				cout<<endl<<"  "<<T("速度 (1快/2中/3慢, 回车=中): ","Speed (1/2/3, Enter=2): ","速度 (1/2/3, Enter=2): ","Tempo (1/2/3, Enter=2): ");
				string spd;
				getline(cin, spd);
				if(spd=="1") gameSpeed = 0;
				else if(spd=="3") gameSpeed = 2;
				else gameSpeed = 1;
			}

			if(difficulty == 5){
				cout<<endl<<"  \033[1;91m"<<T("【警告】雷霆恶魔降临 —— 它已看穿你的下一招","【WARNING】The Thunder Demon descends","【警告】雷霆の悪魔が降臨","【WARNUNG】Der Donnerdaemon naht")<<"\033[0m"<<endl;
				sleep_ms(1200);
			}

			cout<<endl<<"  \033[1;95m"<<T("双手势 (空格分隔两个手势, 费用=两者之和):","Dual moves (space-separated, cost = sum):","双手勢 (スペース区切り、コスト=合計):","Doppelzug (Leerzeichen, Kosten=Summe):")<<"\033[0m"<<endl;
			cout<<"    456 852   456 456   852 852   7913 j   79 13"<<endl<<endl;
			cout<<"  \033[1;96m"<<T("提示: 游戏中输入 ? 或 help 查看完整招式表","Tip: type ? or help in-game","ヒント: ゲーム中 ? または help","Tipp: ? oder help im Spiel")<<"\033[0m"<<endl<<endl;
			wait(1000);

			while(1){
				cout<<endl<<"=========================================="<<endl;
				ai=0; ply=0; flagai=1; flagply=1; lastPlyMove=0;
				int rounds = 0;
				string lastInfo = T("(首回合)","(First round)","(初回)","(Erste Runde)");

				if(aiMood==1) cout<<endl<<"  \033[1;91m[" << T("AI 心情: 激进","AI Mood: Aggressive","AI 気分: 攻撃的","AI-Stimmung: aggressiv") << "]\033[0m";
				else if(aiMood==-1) cout<<endl<<"  \033[1;96m[" << T("AI 心情: 保守","AI Mood: Cautious","AI 気分: 慎重","AI-Stimmung: vorsichtig") << "]\033[0m";

				while(1){
					rounds++;
					cout<<endl;
					if(immersive){
						cout << "  \033[1;90m" << T("上回合: ","Last: ","前回: ","Letzte: ") << lastInfo << "\033[0m" << endl;
						cout << "  \033[1;93m" << T("费: ","Cost: ","費: ","K: ") << ply << " VS " << ai << "\033[0m" << endl;
					} else {
						cout<<"  "<<T("你","You","あなた","Du")<<" "<<ply<<" "<<T("费","c","費","K")<<"      VS      "<<"AI "<<ai<<" "<<T("费","c","費","K")<<endl;
					}
					cout<<endl<<"------------------------------------------"<<endl<<endl;
					if(immersive) cout << aiHint() << endl;
					cout<<T("(拍)请输入 (?, q退出): ","(Slap) Your move (?, q quit): ","(拍)入力 (?, q終了): ","(Klatsch) Dein Zug (?, q beenden): ");

					string line;
					if(!getline(cin, line)){ cin.clear(); continue; }
					istringstream iss(line);
					vector<string> toks;
					string tk;
					while(iss >> tk){ for(auto &ch : tk) ch = tolower(ch); toks.push_back(tk); }
					if(toks.empty()) continue;

					if(toks[0]=="?" || toks[0]=="help"){ showMovesHelp(); continue; }
					if(toks[0]=="q"||toks[0]=="quit"||toks[0]=="exit"){
						cout<<endl<<"  "<<T("确认退出? (y/n): ","Confirm quit? (y/n): ","終了しますか? (y/n): ","Beenden? (y/n): ");
						string cf; getline(cin, cf);
						for(auto &ch : cf) ch = tolower(ch);
						if(cf=="y"||cf=="yes"||cf=="是"||cf=="はい"||cf=="ja") break;
						continue;
					}

					int plydo = -1;
					if(toks.size()==1){ if(too.find(toks[0])!=too.end()) plydo = too[toks[0]]; }
					else if(toks.size()==2){
						if(too.find(toks[0])!=too.end() && too.find(toks[1])!=too.end())
							plydo = combineMoves(too[toks[0]], too[toks[1]]);
					}
					if(plydo < 0){ cout<<endl<<"  "<<T("无效输入","Invalid input","無効","Ungueltig")<<endl; continue; }

					int cur_ai = ai, cur_ply = ply;
					int aido = chooseAI(plydo);
					learn(cur_ai, cur_ply, lastPlyMove, plydo);
					lastPlyMove = plydo;

					cout<<endl<<"=========================================="<<endl<<endl;
					if(immersive){
						battleTheater(aido, plydo);
					} else {
						cout<<"  "<<T("你","You","あなた","Du")<<" "<<ply<<" "<<T("费","c","費","K")<<"      VS      "<<"AI "<<ai<<" "<<T("费","c","費","K")<<endl<<endl;
						cout<<"  "<<T("[你]","[You]","[あなた]","[Du]")<<"  "<<to(plydo)<<endl;
						cout<<"  [AI]  "<<to(aido)<<endl<<endl;
						snd_click();
					}

					flagai = 1; flagply = 1;
					init(aido,plydo);

					int result;
					if(!flagai) result = 0;
					else if(!flagply) result = 1;
					else result = 2;

					lastInfo = T("你","You","あなた","Du") + "[" + to(plydo) + "] vs AI[" + to(aido) + "] -> ";
					if(result==0) lastInfo += T("\033[1;92m你赢\033[0m","\033[1;92mYou win\033[0m","\033[1;92m勝ち\033[0m","\033[1;92mDu gew.\033[0m");
					else if(result==1) lastInfo += T("\033[1;91mAI赢\033[0m","\033[1;91mAI wins\033[0m","\033[1;91mAI勝ち\033[0m","\033[1;91mAI gew.\033[0m");
					else lastInfo += T("\033[1;90m平局\033[0m","\033[1;90mDraw\033[0m","\033[1;90m引き分け\033[0m","\033[1;90mUnentsch.\033[0m");

					if(!solve(plydo, aido, rounds)){
						if(flagai==0){ stats.hsW++; if(difficulty == 5) unlock("demon"); updateMood(true); }
						else { stats.hsL++; updateMood(false); }
						saveStats();
						break;
					}
					cout<<"  >>> "<<cheer(2)<<" "<<face(2)<<endl<<endl;
					sdelay(450);
				}

				cout<<endl<<T("再玩一局? (y/n, q退出): ","Play again? (y/n, q quit): ","もう一回? (y/n, q終了): ","Nochmal? (y/n, q beenden): ");
				string c;
				if(!getline(cin, c)){ cin.clear(); continue; }
				{ istringstream i2(c); string t2; if(i2 >> t2){ for(auto &ch : t2) ch = tolower(ch); c = t2; } else c = ""; }
				if(c=="n"||c=="no"||c=="q"||c=="quit"||c=="exit") break;
			}
			saveLearn("ai_memory.txt");
			saveStats();
		}

		if(game==2){ tutorial(2); rps(); }
		if(game==3){ tutorial(3); gomoku(); }
		if(game==4){ tutorial(4); maze_game(); }
		if(game==5){ tutorial(5); squid_game(); }
		if(game==6){ tutorial(6); liars_bar(); }
	}

	saveLearn("ai_memory.txt");
	saveStats();
	outro();
	return 0;
}
