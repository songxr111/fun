from http.server import BaseHTTPRequestHandler, HTTPServer
from socketserver import ThreadingMixIn
from urllib.parse import parse_qs
from datetime import datetime
import hashlib
import re
import html
import subprocess
import os
import sys
import hashlib
import requests

class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """多线程HTTP服务器"""

class ChatHandler(BaseHTTPRequestHandler):
    sessions = {} 
    ban = {}
    messages = []
    banall = False
    
    def parse_post_data(self):
        content_length = int(self.headers.get('Content-Length', 0))
        return parse_qs(self.rfile.read(content_length).decode('utf-8'))
    
    def _set_headers(self):
        self.send_header('Content-type', 'text/html; charset=utf-8')
        self.end_headers()
    
    def get_session_username(self):
        """从cookie获取当前会话的用户名"""
        cookie = self.headers.get('Cookie', '')
        session_match = re.search(r'session=([a-f0-9]+)', cookie)
        if session_match:
            session_id = session_match.group(1)
            return self.sessions.get(session_id)
        return None
    
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self._set_headers()
            username = self.get_session_username()
            content = self.generate_chat_html() if username else self.generate_login_html()
            self.wfile.write(content.encode('utf-8'))
        elif self.path == '/logout':
            self.handle_logout()
        elif self.path == '/message':
            self.send_response(200)
            self._set_headers()
            content = self.generate_message_html()
            self.wfile.write(content.encode('utf-8'))
        else:
            self.send_error(404, "页面不存在")

    def handle_logout(self):
        """处理登出"""
        cookie = self.headers.get('Cookie', '')
        session_match = re.search(r'session=([a-f0-9]+)', cookie)
        if session_match:
            session_id = session_match.group(1)
            self.sessions.pop(session_id, None)
        
        self.send_response(303)
        self.send_header('Set-Cookie', 'session=; expires=Thu, 01 Jan 1970 00:00:00 GMT')
        self.send_header('Location', '/')
        self.end_headers()

    def check_credentials(self, username, password):
        api_url = "http://jx.7fa4.cn:8888/api/login"
    
        salted_password = password + "syzoj2_xxx"
        hashed_password = hashlib.md5(salted_password.encode()).hexdigest()
        
        payload = {
            "username": username,
            "password": hashed_password
        }

        try:
            response = requests.post(api_url, data=payload)
            
            if response.status_code == 200:
                try:
                    response_data = response.json()
                    error_code = response_data.get("error_code")
                    if error_code == 1:
                        return 1
                    else:
                        return 0
                except ValueError: 
                    return 0
            else:
                return 0
            return 0

    def do_POST(self):
        if self.path == '/login':
            post_data = self.parse_post_data()
            username = post_data.get('username', [''])[0].strip()
            password = post_data.get('password', [''])[0]
            
            # 验证用户名和密码
            if username and password and self.check_credentials(username, password):
                # 创建会话
                session_id = hashlib.md5(f"{username}{datetime.now()}".encode()).hexdigest()
                self.sessions[session_id] = username
                
                self.send_response(303)
                self.send_header('Set-Cookie', f'session={session_id}')
                self.send_header('Location', '/')
                self.end_headers()
            else:
                self.send_response(200)
                self._set_headers()
                error_html = self.generate_login_html("用户名或密码错误")
                self.wfile.write(error_html.encode('utf-8'))
                
        elif self.path == '/send':
            username = self.get_session_username()
            if not username:
                self.send_error(403, "请先登录")
                return
                
            post_data = self.parse_post_data()
            message = post_data.get('message', [''])[0]
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            
            if username == 'for_fo_f':
                if '\\ban' in message:
                    target_user = message.split()[-1]
                    self.ban[target_user] = 1
                    message = f'<系统消息>已封禁用户: {target_user}'
                elif '\\unban' in message:
                    target_user = message.split()[-1]
                    self.ban[target_user] = 0
                    message = f'<系统消息>已解封用户: {target_user}'
                elif '\\clear' in message:
                    self.messages.clear()
                    message = f'<系统消息>已清空聊天记录'
                elif '\\all_ban' in message:
                    ChatHandler.banall = True
                    message = f'<系统消息>已开启全员禁言'
                elif '\\all_unban' in message:
                    ChatHandler.banall = False
                    message = f'<系统消息>已关闭全员禁言'
            
            if username not in self.ban or self.ban[username] == 0:
                if not self.banall or username == 'for_fo_f':
                    self.messages.append({
                        'username': username,
                        'message': html.escape(message),
                        'timestamp': timestamp
                    })
            
            self.send_response(303)
            self.send_header('Location', '/')
            self.end_headers()

    def generate_login_html(self, error_message=None):
        error_html = f'<div style="color: red; margin-bottom: 10px;">{error_message}</div>' if error_message else ''
        return f'''
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <title>用户登录</title>
            <style>
                body {{
                    font-family: 'Segoe UI', system-ui;
                    background: #f0f2f5;
                    height: 100vh;
                    margin: 0;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                }}
                .card {{
                    background: white;
                    padding: 2rem;
                    border-radius: 10px;
                    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
                    width: 320px;
                }}
                h1 {{
                    color: #1a73e8;
                    margin: 0 0 2rem 0;
                    text-align: center;
                }}
                input {{
                    width: 100%;
                    padding: 8px;
                    margin: 6px 0;
                    border: 1px solid #ddd;
                    border-radius: 4px;
                    box-sizing: border-box;
                }}
                input[type="submit"] {{
                    background: #1a73e8;
                    color: white;
                    border: none;
                    padding: 10px;
                    margin-top: 1rem;
                    cursor: pointer;
                    transition: background 0.3s;
                }}
                input[type="submit"]:hover {{
                    background: #1557b0;
                }}
            </style>
        </head>
        <body>
            <div class="card">
                <h1>用户登录</h1>
                {error_html}
                <form method="post" action="/login">
                    <input type="text" name="username" placeholder="用户名" required>
                    <input type="password" name="password" placeholder="密码" required>
                    <input type="submit" value="登录">
                </form>
            </div>
        </body>
        </html>
        '''
    
    def generate_chat_html(self):
        username = self.get_session_username()
        return f'''
        <!DOCTYPE html>
        <html>
        <head>
            <meta charset="UTF-8">
            <title>Chat Room</title>
            <style>
                .logout-btn {{
                    color: #dc3545;
                    text-decoration: none;
                    margin-left: 20px;
                    padding: 6px 12px;
                    border: 1px solid #dc3545;
                    border-radius: 4px;
                    transition: all 0.3s;
                }}
                .logout-btn:hover {{
                    background: #dc3545;
                    color: white;
                }}
                * {{
                    box-sizing: border-box;
                    margin: 0;
                    padding: 0;
                }}
                body {{
                    font-family: 'Segoe UI', system-ui;
                    height: 100vh;
                    display: flex;
                    background: #f0f2f5;
                }}
                .container {{
                    flex: 1;
                    display: flex;
                    flex-direction: column;
                    max-width: 1200px;
                    margin: 0 auto;
                    width: 95%;
                    padding: 20px 0;
                }}
                .messages {{
                    flex: 1;
                    overflow-y: auto;
                    padding: 15px;
                    background: white;
                    border-radius: 8px;
                    box-shadow: 0 2px 4px rgba(0,0,0,0.05);
                    margin-bottom: 15px;
                }}
                .message {{
                    margin: 10px 0;
                    padding: 12px;
                    background: #f1f3f4;
                    border-radius: 12px;
                    max-width: 80%;
                    word-break: break-word;
                    animation: fadeIn 0.3s ease-in;
                }}
                .message.self {{
                    background: #1a73e8;
                    color: white;
                    margin-left: auto;
                }}
                .username {{
                    font-weight: 600;
                    font-size: 0.9em;
                    color: #1a73e8;
                    margin-bottom: 4px;
                }}
                .message.self .username {{
                    color: #e3f2fd;
                }}
                .timestamp {{
                    color: #666;
                    font-size: 0.8em;
                    margin-left: 8px;
                }}
                .message.self .timestamp {{
                    color: #e0e0e0;
                }}
                form {{
                    background: white;
                    padding: 15px;
                    border-radius: 8px;
                    box-shadow: 0 2px 4px rgba(0,0,0,0.05);
                    display: flex;
                    gap: 10px;
                }}
                input[type="text"] {{
                    flex: 1;
                    padding: 12px;
                    border: 1px solid #ddd;
                    border-radius: 6px;
                    font-size: 1em;
                }}
                input[type="submit"] {{
                    background: #1a73e8;
                    color: white;
                    border: none;
                    padding: 12px 24px;
                    border-radius: 6px;
                    cursor: pointer;
                    transition: background 0.2s;
                }}
                @keyframes fadeIn {{
                    from {{ opacity: 0; transform: translateY(10px); }}
                    to {{ opacity: 1; transform: translateY(0); }}
                }}
                @media (max-width: 600px) {{
                    .container {{
                        width: 100%;
                        padding: 10px;
                    }}
                    .message {{
                        max-width: 90%;
                        padding: 10px;
                    }}
                }}
            </style>
            <script data-cfasync="false" src="http://jx.7fa4.cn:8888/cdnjs/jquery/3.3.1/jquery.min.js"></script>
        </head>
        <body>
            <div class="container">
                <div class="messages" id="messages">
                </div>
                <div style="display: flex; justify-content: space-between; align-items: center;">
                    <form method="post" action="/send" style="flex:1">
                        <input type="text" name="message" placeholder="输入消息..." autofocus>
                        <input type="submit" value="发送">
                    </form>
                    <a href="/logout" class="logout-btn">退出登录</a>
                </div>
            </div>
            <script>
                let lst;
                function reload(){{
                    $.get('/message',ret=>{{
                        if(lst!=ret){{
                            messages.innerHTML=ret;
                            lst=ret;
                            messages.scrollTop = messages.scrollHeight;
                            
                        }}
                    }});
                    setTimeout(()=>reload(), 1000);
                }}
        reload();
            </script>
        </body>
        </html>
        '''
    
    def generate_message_html(self):
        username = self.get_session_username()
        
        messages_html = []
        for msg in self.messages:
            is_self = msg['username'] == username
            messages_html.append(f'''
            <div class="message {'self' if is_self else ''}">
                <span class="username">{html.escape(msg['username'])}</span>
                <span class="timestamp">{msg['timestamp']}</span>
                <p>{msg['message']}</p>
            </div>
            ''')
        return '\n'.join(messages_html)

if __name__ == '__main__':
    port = 8888
    server_address = ('', port)
    httpd = ThreadedHTTPServer(server_address, ChatHandler)
    print(f"服务器运行在端口 {port}")
    httpd.serve_forever()
