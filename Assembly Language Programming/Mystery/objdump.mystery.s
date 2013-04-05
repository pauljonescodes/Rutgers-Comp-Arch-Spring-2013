00000000 <add>:
0:   55                      push   ebp
1:   89 e5                   mov    ebp,esp
3:   8b 45 0c                mov    eax,DWORD PTR [ebp+0xc]
6:   03 45 08                add    eax,DWORD PTR [ebp+0x8]
9:   5d                      pop    ebp
a:   c3                      ret

0000000b <compute_fib>:
b:   55                      push   ebp
c:   89 e5                   mov    ebp,esp
e:   53                      push   ebx
f:   83 ec 1c                sub    esp,0x1c
12:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
15:   8b 04 85 00 00 00 00    mov    eax,DWORD PTR [eax*4+0x0]
1c:   83 f8 ff                cmp    eax,0xffffffff
1f:   74 0f                   je     30 <compute_fib+0x25>
21:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
24:   8b 04 85 00 00 00 00    mov    eax,DWORD PTR [eax*4+0x0]
2b:   89 45 e8                mov    DWORD PTR [ebp-0x18],eax
2e:   eb 7b                   jmp    ab <compute_fib+0xa0>
30:   c7 45 f8 ff ff ff ff    mov    DWORD PTR [ebp-0x8],0xffffffff
37:   83 7d 08 00             cmp    DWORD PTR [ebp+0x8],0x0
3b:   75 09                   jne    46 <compute_fib+0x3b>
3d:   c7 45 f8 00 00 00 00    mov    DWORD PTR [ebp-0x8],0x0
44:   eb 3c                   jmp    82 <compute_fib+0x77>
46:   83 7d 08 01             cmp    DWORD PTR [ebp+0x8],0x1
4a:   75 09                   jne    55 <compute_fib+0x4a>
4c:   c7 45 f8 01 00 00 00    mov    DWORD PTR [ebp-0x8],0x1
53:   eb 2d                   jmp    82 <compute_fib+0x77>
55:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
58:   83 e8 02                sub    eax,0x2
5b:   89 04 24                mov    DWORD PTR [esp],eax
5e:   e8 fc ff ff ff          call   5f <compute_fib+0x54>
63:   89 c3                   mov    ebx,eax
65:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
68:   83 e8 01                sub    eax,0x1
6b:   89 04 24                mov    DWORD PTR [esp],eax
6e:   e8 fc ff ff ff          call   6f <compute_fib+0x64>
73:   89 5c 24 04             mov    DWORD PTR [esp+0x4],ebx
77:   89 04 24                mov    DWORD PTR [esp],eax
7a:   e8 fc ff ff ff          call   7b <compute_fib+0x70>
7f:   89 45 f8                mov    DWORD PTR [ebp-0x8],eax
82:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
85:   8b 04 85 00 00 00 00    mov    eax,DWORD PTR [eax*4+0x0]
8c:   83 f8 ff                cmp    eax,0xffffffff
8f:   75 0d                   jne    9e <compute_fib+0x93>
91:   8b 55 08                mov    edx,DWORD PTR [ebp+0x8]
94:   8b 45 f8                mov    eax,DWORD PTR [ebp-0x8]
97:   89 04 95 00 00 00 00    mov    DWORD PTR [edx*4+0x0],eax
9e:   8b 45 08                mov    eax,DWORD PTR [ebp+0x8]
a1:   8b 04 85 00 00 00 00    mov    eax,DWORD PTR [eax*4+0x0]
a8:   89 45 e8                mov    DWORD PTR [ebp-0x18],eax
ab:   8b 45 e8                mov    eax,DWORD PTR [ebp-0x18]
ae:   83 c4 1c                add    esp,0x1c
b1:   5b                      pop    ebx
b2:   5d                      pop    ebp
b3:   c3                      ret

000000b4 <main>:
b4:   8d 4c 24 04             lea    ecx,[esp+0x4]
b8:   83 e4 f0                and    esp,0xfffffff0
bb:   ff 71 fc                push   DWORD PTR [ecx-0x4]
be:   55                      push   ebp
bf:   89 e5                   mov    ebp,esp
c1:   51                      push   ecx
c2:   83 ec 24                sub    esp,0x24
c5:   8b 41 04                mov    eax,DWORD PTR [ecx+0x4]
c8:   83 c0 04                add    eax,0x4
cb:   8b 00                   mov    eax,DWORD PTR [eax]
cd:   89 04 24                mov    DWORD PTR [esp],eax
d0:   e8 fc ff ff ff          call   d1 <main+0x1d>
d5:   89 45 f4                mov    DWORD PTR [ebp-0xc],eax
d8:   c7 45 f8 00 00 00 00    mov    DWORD PTR [ebp-0x8],0x0
df:   eb 12                   jmp    f3 <main+0x3f>
e1:   8b 45 f8                mov    eax,DWORD PTR [ebp-0x8]
e4:   c7 04 85 00 00 00 00    mov    DWORD PTR [eax*4+0x0],0xffffffff
eb:   ff ff ff ff
ef:   83 45 f8 01             add    DWORD PTR [ebp-0x8],0x1
f3:   81 7d f8 c7 00 00 00    cmp    DWORD PTR [ebp-0x8],0xc7
fa:   7e e5                   jle    e1 <main+0x2d>
fc:   8b 45 f4                mov    eax,DWORD PTR [ebp-0xc]
ff:   89 04 24                mov    DWORD PTR [esp],eax
102:   e8 fc ff ff ff          call   103 <main+0x4f>
107:   89 44 24 04             mov    DWORD PTR [esp+0x4],eax
10b:   c7 04 24 00 00 00 00    mov    DWORD PTR [esp],0x0
112:   e8 fc ff ff ff          call   113 <main+0x5f>
117:   b8 00 00 00 00          mov    eax,0x0
11c:   83 c4 24                add    esp,0x24
11f:   59                      pop    ecx
120:   5d                      pop    ebp
121:   8d 61 fc                lea    esp,[ecx-0x4]
124:   c3                      ret