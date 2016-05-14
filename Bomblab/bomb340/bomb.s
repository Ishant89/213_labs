
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000400b38 <_init>:
  400b38:	48 83 ec 08          	sub    $0x8,%rsp
  400b3c:	e8 1b 02 00 00       	callq  400d5c <call_gmon_start>
  400b41:	e8 aa 02 00 00       	callq  400df0 <frame_dummy>
  400b46:	e8 05 1b 00 00       	callq  402650 <__do_global_ctors_aux>
  400b4b:	48 83 c4 08          	add    $0x8,%rsp
  400b4f:	c3                   	retq   

Disassembly of section .plt:

0000000000400b50 <getenv@plt-0x10>:
  400b50:	ff 35 9a 34 20 00    	pushq  0x20349a(%rip)        # 603ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400b56:	ff 25 9c 34 20 00    	jmpq   *0x20349c(%rip)        # 603ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  400b5c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400b60 <getenv@plt>:
  400b60:	ff 25 9a 34 20 00    	jmpq   *0x20349a(%rip)        # 604000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400b66:	68 00 00 00 00       	pushq  $0x0
  400b6b:	e9 e0 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400b70 <strcasecmp@plt>:
  400b70:	ff 25 92 34 20 00    	jmpq   *0x203492(%rip)        # 604008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400b76:	68 01 00 00 00       	pushq  $0x1
  400b7b:	e9 d0 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400b80 <__errno_location@plt>:
  400b80:	ff 25 8a 34 20 00    	jmpq   *0x20348a(%rip)        # 604010 <_GLOBAL_OFFSET_TABLE_+0x28>
  400b86:	68 02 00 00 00       	pushq  $0x2
  400b8b:	e9 c0 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400b90 <strcpy@plt>:
  400b90:	ff 25 82 34 20 00    	jmpq   *0x203482(%rip)        # 604018 <_GLOBAL_OFFSET_TABLE_+0x30>
  400b96:	68 03 00 00 00       	pushq  $0x3
  400b9b:	e9 b0 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400ba0 <puts@plt>:
  400ba0:	ff 25 7a 34 20 00    	jmpq   *0x20347a(%rip)        # 604020 <_GLOBAL_OFFSET_TABLE_+0x38>
  400ba6:	68 04 00 00 00       	pushq  $0x4
  400bab:	e9 a0 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400bb0 <write@plt>:
  400bb0:	ff 25 72 34 20 00    	jmpq   *0x203472(%rip)        # 604028 <_GLOBAL_OFFSET_TABLE_+0x40>
  400bb6:	68 05 00 00 00       	pushq  $0x5
  400bbb:	e9 90 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400bc0 <__stack_chk_fail@plt>:
  400bc0:	ff 25 6a 34 20 00    	jmpq   *0x20346a(%rip)        # 604030 <_GLOBAL_OFFSET_TABLE_+0x48>
  400bc6:	68 06 00 00 00       	pushq  $0x6
  400bcb:	e9 80 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400bd0 <alarm@plt>:
  400bd0:	ff 25 62 34 20 00    	jmpq   *0x203462(%rip)        # 604038 <_GLOBAL_OFFSET_TABLE_+0x50>
  400bd6:	68 07 00 00 00       	pushq  $0x7
  400bdb:	e9 70 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400be0 <close@plt>:
  400be0:	ff 25 5a 34 20 00    	jmpq   *0x20345a(%rip)        # 604040 <_GLOBAL_OFFSET_TABLE_+0x58>
  400be6:	68 08 00 00 00       	pushq  $0x8
  400beb:	e9 60 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400bf0 <read@plt>:
  400bf0:	ff 25 52 34 20 00    	jmpq   *0x203452(%rip)        # 604048 <_GLOBAL_OFFSET_TABLE_+0x60>
  400bf6:	68 09 00 00 00       	pushq  $0x9
  400bfb:	e9 50 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c00 <__libc_start_main@plt>:
  400c00:	ff 25 4a 34 20 00    	jmpq   *0x20344a(%rip)        # 604050 <_GLOBAL_OFFSET_TABLE_+0x68>
  400c06:	68 0a 00 00 00       	pushq  $0xa
  400c0b:	e9 40 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c10 <fgets@plt>:
  400c10:	ff 25 42 34 20 00    	jmpq   *0x203442(%rip)        # 604058 <_GLOBAL_OFFSET_TABLE_+0x70>
  400c16:	68 0b 00 00 00       	pushq  $0xb
  400c1b:	e9 30 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c20 <signal@plt>:
  400c20:	ff 25 3a 34 20 00    	jmpq   *0x20343a(%rip)        # 604060 <_GLOBAL_OFFSET_TABLE_+0x78>
  400c26:	68 0c 00 00 00       	pushq  $0xc
  400c2b:	e9 20 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c30 <gethostbyname@plt>:
  400c30:	ff 25 32 34 20 00    	jmpq   *0x203432(%rip)        # 604068 <_GLOBAL_OFFSET_TABLE_+0x80>
  400c36:	68 0d 00 00 00       	pushq  $0xd
  400c3b:	e9 10 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c40 <__memmove_chk@plt>:
  400c40:	ff 25 2a 34 20 00    	jmpq   *0x20342a(%rip)        # 604070 <_GLOBAL_OFFSET_TABLE_+0x88>
  400c46:	68 0e 00 00 00       	pushq  $0xe
  400c4b:	e9 00 ff ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c50 <__memcpy_chk@plt>:
  400c50:	ff 25 22 34 20 00    	jmpq   *0x203422(%rip)        # 604078 <_GLOBAL_OFFSET_TABLE_+0x90>
  400c56:	68 0f 00 00 00       	pushq  $0xf
  400c5b:	e9 f0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c60 <strtol@plt>:
  400c60:	ff 25 1a 34 20 00    	jmpq   *0x20341a(%rip)        # 604080 <_GLOBAL_OFFSET_TABLE_+0x98>
  400c66:	68 10 00 00 00       	pushq  $0x10
  400c6b:	e9 e0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c70 <fflush@plt>:
  400c70:	ff 25 12 34 20 00    	jmpq   *0x203412(%rip)        # 604088 <_GLOBAL_OFFSET_TABLE_+0xa0>
  400c76:	68 11 00 00 00       	pushq  $0x11
  400c7b:	e9 d0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c80 <__isoc99_sscanf@plt>:
  400c80:	ff 25 0a 34 20 00    	jmpq   *0x20340a(%rip)        # 604090 <_GLOBAL_OFFSET_TABLE_+0xa8>
  400c86:	68 12 00 00 00       	pushq  $0x12
  400c8b:	e9 c0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400c90 <__printf_chk@plt>:
  400c90:	ff 25 02 34 20 00    	jmpq   *0x203402(%rip)        # 604098 <_GLOBAL_OFFSET_TABLE_+0xb0>
  400c96:	68 13 00 00 00       	pushq  $0x13
  400c9b:	e9 b0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400ca0 <fopen@plt>:
  400ca0:	ff 25 fa 33 20 00    	jmpq   *0x2033fa(%rip)        # 6040a0 <_GLOBAL_OFFSET_TABLE_+0xb8>
  400ca6:	68 14 00 00 00       	pushq  $0x14
  400cab:	e9 a0 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400cb0 <gethostname@plt>:
  400cb0:	ff 25 f2 33 20 00    	jmpq   *0x2033f2(%rip)        # 6040a8 <_GLOBAL_OFFSET_TABLE_+0xc0>
  400cb6:	68 15 00 00 00       	pushq  $0x15
  400cbb:	e9 90 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400cc0 <exit@plt>:
  400cc0:	ff 25 ea 33 20 00    	jmpq   *0x2033ea(%rip)        # 6040b0 <_GLOBAL_OFFSET_TABLE_+0xc8>
  400cc6:	68 16 00 00 00       	pushq  $0x16
  400ccb:	e9 80 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400cd0 <connect@plt>:
  400cd0:	ff 25 e2 33 20 00    	jmpq   *0x2033e2(%rip)        # 6040b8 <_GLOBAL_OFFSET_TABLE_+0xd0>
  400cd6:	68 17 00 00 00       	pushq  $0x17
  400cdb:	e9 70 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400ce0 <__fprintf_chk@plt>:
  400ce0:	ff 25 da 33 20 00    	jmpq   *0x2033da(%rip)        # 6040c0 <_GLOBAL_OFFSET_TABLE_+0xd8>
  400ce6:	68 18 00 00 00       	pushq  $0x18
  400ceb:	e9 60 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400cf0 <sleep@plt>:
  400cf0:	ff 25 d2 33 20 00    	jmpq   *0x2033d2(%rip)        # 6040c8 <_GLOBAL_OFFSET_TABLE_+0xe0>
  400cf6:	68 19 00 00 00       	pushq  $0x19
  400cfb:	e9 50 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400d00 <__ctype_b_loc@plt>:
  400d00:	ff 25 ca 33 20 00    	jmpq   *0x2033ca(%rip)        # 6040d0 <_GLOBAL_OFFSET_TABLE_+0xe8>
  400d06:	68 1a 00 00 00       	pushq  $0x1a
  400d0b:	e9 40 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400d10 <__sprintf_chk@plt>:
  400d10:	ff 25 c2 33 20 00    	jmpq   *0x2033c2(%rip)        # 6040d8 <_GLOBAL_OFFSET_TABLE_+0xf0>
  400d16:	68 1b 00 00 00       	pushq  $0x1b
  400d1b:	e9 30 fe ff ff       	jmpq   400b50 <_init+0x18>

0000000000400d20 <socket@plt>:
  400d20:	ff 25 ba 33 20 00    	jmpq   *0x2033ba(%rip)        # 6040e0 <_GLOBAL_OFFSET_TABLE_+0xf8>
  400d26:	68 1c 00 00 00       	pushq  $0x1c
  400d2b:	e9 20 fe ff ff       	jmpq   400b50 <_init+0x18>

Disassembly of section .text:

0000000000400d30 <_start>:
  400d30:	31 ed                	xor    %ebp,%ebp
  400d32:	49 89 d1             	mov    %rdx,%r9
  400d35:	5e                   	pop    %rsi
  400d36:	48 89 e2             	mov    %rsp,%rdx
  400d39:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400d3d:	50                   	push   %rax
  400d3e:	54                   	push   %rsp
  400d3f:	49 c7 c0 40 26 40 00 	mov    $0x402640,%r8
  400d46:	48 c7 c1 b0 25 40 00 	mov    $0x4025b0,%rcx
  400d4d:	48 c7 c7 14 0e 40 00 	mov    $0x400e14,%rdi
  400d54:	e8 a7 fe ff ff       	callq  400c00 <__libc_start_main@plt>
  400d59:	f4                   	hlt    
  400d5a:	90                   	nop
  400d5b:	90                   	nop

0000000000400d5c <call_gmon_start>:
  400d5c:	48 83 ec 08          	sub    $0x8,%rsp
  400d60:	48 8b 05 79 32 20 00 	mov    0x203279(%rip),%rax        # 603fe0 <_DYNAMIC+0x190>
  400d67:	48 85 c0             	test   %rax,%rax
  400d6a:	74 02                	je     400d6e <call_gmon_start+0x12>
  400d6c:	ff d0                	callq  *%rax
  400d6e:	48 83 c4 08          	add    $0x8,%rsp
  400d72:	c3                   	retq   
  400d73:	90                   	nop
  400d74:	90                   	nop
  400d75:	90                   	nop
  400d76:	90                   	nop
  400d77:	90                   	nop
  400d78:	90                   	nop
  400d79:	90                   	nop
  400d7a:	90                   	nop
  400d7b:	90                   	nop
  400d7c:	90                   	nop
  400d7d:	90                   	nop
  400d7e:	90                   	nop
  400d7f:	90                   	nop

0000000000400d80 <__do_global_dtors_aux>:
  400d80:	55                   	push   %rbp
  400d81:	48 89 e5             	mov    %rsp,%rbp
  400d84:	53                   	push   %rbx
  400d85:	48 83 ec 08          	sub    $0x8,%rsp
  400d89:	80 3d 88 48 20 00 00 	cmpb   $0x0,0x204888(%rip)        # 605618 <completed.6531>
  400d90:	75 4b                	jne    400ddd <__do_global_dtors_aux+0x5d>
  400d92:	bb 40 3e 60 00       	mov    $0x603e40,%ebx
  400d97:	48 8b 05 82 48 20 00 	mov    0x204882(%rip),%rax        # 605620 <dtor_idx.6533>
  400d9e:	48 81 eb 38 3e 60 00 	sub    $0x603e38,%rbx
  400da5:	48 c1 fb 03          	sar    $0x3,%rbx
  400da9:	48 83 eb 01          	sub    $0x1,%rbx
  400dad:	48 39 d8             	cmp    %rbx,%rax
  400db0:	73 24                	jae    400dd6 <__do_global_dtors_aux+0x56>
  400db2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400db8:	48 83 c0 01          	add    $0x1,%rax
  400dbc:	48 89 05 5d 48 20 00 	mov    %rax,0x20485d(%rip)        # 605620 <dtor_idx.6533>
  400dc3:	ff 14 c5 38 3e 60 00 	callq  *0x603e38(,%rax,8)
  400dca:	48 8b 05 4f 48 20 00 	mov    0x20484f(%rip),%rax        # 605620 <dtor_idx.6533>
  400dd1:	48 39 d8             	cmp    %rbx,%rax
  400dd4:	72 e2                	jb     400db8 <__do_global_dtors_aux+0x38>
  400dd6:	c6 05 3b 48 20 00 01 	movb   $0x1,0x20483b(%rip)        # 605618 <completed.6531>
  400ddd:	48 83 c4 08          	add    $0x8,%rsp
  400de1:	5b                   	pop    %rbx
  400de2:	5d                   	pop    %rbp
  400de3:	c3                   	retq   
  400de4:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400deb:	00 00 00 00 00 

0000000000400df0 <frame_dummy>:
  400df0:	48 83 3d 50 30 20 00 	cmpq   $0x0,0x203050(%rip)        # 603e48 <__JCR_END__>
  400df7:	00 
  400df8:	55                   	push   %rbp
  400df9:	48 89 e5             	mov    %rsp,%rbp
  400dfc:	74 12                	je     400e10 <frame_dummy+0x20>
  400dfe:	b8 00 00 00 00       	mov    $0x0,%eax
  400e03:	48 85 c0             	test   %rax,%rax
  400e06:	74 08                	je     400e10 <frame_dummy+0x20>
  400e08:	5d                   	pop    %rbp
  400e09:	bf 48 3e 60 00       	mov    $0x603e48,%edi
  400e0e:	ff e0                	jmpq   *%rax
  400e10:	5d                   	pop    %rbp
  400e11:	c3                   	retq   
  400e12:	90                   	nop
  400e13:	90                   	nop

0000000000400e14 <main>:
  400e14:	53                   	push   %rbx
  400e15:	48 89 f3             	mov    %rsi,%rbx
  400e18:	83 ff 01             	cmp    $0x1,%edi
  400e1b:	75 10                	jne    400e2d <main+0x19>
  400e1d:	48 8b 05 e4 47 20 00 	mov    0x2047e4(%rip),%rax        # 605608 <stdin@@GLIBC_2.2.5>
  400e24:	48 89 05 05 48 20 00 	mov    %rax,0x204805(%rip)        # 605630 <infile>
  400e2b:	eb 60                	jmp    400e8d <main+0x79>
  400e2d:	83 ff 02             	cmp    $0x2,%edi
  400e30:	75 3a                	jne    400e6c <main+0x58>
  400e32:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  400e36:	be a4 26 40 00       	mov    $0x4026a4,%esi
  400e3b:	e8 60 fe ff ff       	callq  400ca0 <fopen@plt>
  400e40:	48 89 05 e9 47 20 00 	mov    %rax,0x2047e9(%rip)        # 605630 <infile>
  400e47:	48 85 c0             	test   %rax,%rax
  400e4a:	75 41                	jne    400e8d <main+0x79>
  400e4c:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
  400e50:	48 8b 13             	mov    (%rbx),%rdx
  400e53:	be a6 26 40 00       	mov    $0x4026a6,%esi
  400e58:	bf 01 00 00 00       	mov    $0x1,%edi
  400e5d:	e8 2e fe ff ff       	callq  400c90 <__printf_chk@plt>
  400e62:	bf 08 00 00 00       	mov    $0x8,%edi
  400e67:	e8 54 fe ff ff       	callq  400cc0 <exit@plt>
  400e6c:	48 8b 16             	mov    (%rsi),%rdx
  400e6f:	be c3 26 40 00       	mov    $0x4026c3,%esi
  400e74:	bf 01 00 00 00       	mov    $0x1,%edi
  400e79:	b8 00 00 00 00       	mov    $0x0,%eax
  400e7e:	e8 0d fe ff ff       	callq  400c90 <__printf_chk@plt>
  400e83:	bf 08 00 00 00       	mov    $0x8,%edi
  400e88:	e8 33 fe ff ff       	callq  400cc0 <exit@plt>
  400e8d:	e8 43 05 00 00       	callq  4013d5 <initialize_bomb>
  400e92:	bf 28 27 40 00       	mov    $0x402728,%edi
  400e97:	e8 04 fd ff ff       	callq  400ba0 <puts@plt>
  400e9c:	bf 68 27 40 00       	mov    $0x402768,%edi
  400ea1:	e8 fa fc ff ff       	callq  400ba0 <puts@plt>
  400ea6:	e8 e4 07 00 00       	callq  40168f <read_line>
  400eab:	48 89 c7             	mov    %rax,%rdi
  400eae:	e8 9d 00 00 00       	callq  400f50 <phase_1>
  400eb3:	e8 44 09 00 00       	callq  4017fc <phase_defused>
  400eb8:	bf 98 27 40 00       	mov    $0x402798,%edi
  400ebd:	e8 de fc ff ff       	callq  400ba0 <puts@plt>
  400ec2:	e8 c8 07 00 00       	callq  40168f <read_line>
  400ec7:	48 89 c7             	mov    %rax,%rdi
  400eca:	e8 9d 00 00 00       	callq  400f6c <phase_2>
  400ecf:	e8 28 09 00 00       	callq  4017fc <phase_defused>
  400ed4:	bf dd 26 40 00       	mov    $0x4026dd,%edi
  400ed9:	e8 c2 fc ff ff       	callq  400ba0 <puts@plt>
  400ede:	e8 ac 07 00 00       	callq  40168f <read_line>
  400ee3:	48 89 c7             	mov    %rax,%rdi
  400ee6:	e8 c2 00 00 00       	callq  400fad <phase_3>
  400eeb:	e8 0c 09 00 00       	callq  4017fc <phase_defused>
  400ef0:	bf fb 26 40 00       	mov    $0x4026fb,%edi
  400ef5:	e8 a6 fc ff ff       	callq  400ba0 <puts@plt>
  400efa:	e8 90 07 00 00       	callq  40168f <read_line>
  400eff:	48 89 c7             	mov    %rax,%rdi
  400f02:	e8 6f 01 00 00       	callq  401076 <phase_4>
  400f07:	e8 f0 08 00 00       	callq  4017fc <phase_defused>
  400f0c:	bf c8 27 40 00       	mov    $0x4027c8,%edi
  400f11:	e8 8a fc ff ff       	callq  400ba0 <puts@plt>
  400f16:	e8 74 07 00 00       	callq  40168f <read_line>
  400f1b:	48 89 c7             	mov    %rax,%rdi
  400f1e:	e8 b0 01 00 00       	callq  4010d3 <phase_5>
  400f23:	e8 d4 08 00 00       	callq  4017fc <phase_defused>
  400f28:	bf 0a 27 40 00       	mov    $0x40270a,%edi
  400f2d:	e8 6e fc ff ff       	callq  400ba0 <puts@plt>
  400f32:	e8 58 07 00 00       	callq  40168f <read_line>
  400f37:	48 89 c7             	mov    %rax,%rdi
  400f3a:	e8 d5 01 00 00       	callq  401114 <phase_6>
  400f3f:	e8 b8 08 00 00       	callq  4017fc <phase_defused>
  400f44:	b8 00 00 00 00       	mov    $0x0,%eax
  400f49:	5b                   	pop    %rbx
  400f4a:	c3                   	retq   
  400f4b:	90                   	nop
  400f4c:	90                   	nop
  400f4d:	90                   	nop
  400f4e:	90                   	nop
  400f4f:	90                   	nop

0000000000400f50 <phase_1>:
  400f50:	48 83 ec 08          	sub    $0x8,%rsp
  400f54:	be f0 27 40 00       	mov    $0x4027f0,%esi
  400f59:	e8 f9 03 00 00       	callq  401357 <strings_not_equal>
  400f5e:	85 c0                	test   %eax,%eax
  400f60:	74 05                	je     400f67 <phase_1+0x17>
  400f62:	e8 f2 06 00 00       	callq  401659 <explode_bomb>
  400f67:	48 83 c4 08          	add    $0x8,%rsp
  400f6b:	c3                   	retq   

0000000000400f6c <phase_2>:
  400f6c:	55                   	push   %rbp
  400f6d:	53                   	push   %rbx
  400f6e:	48 83 ec 28          	sub    $0x28,%rsp
  400f72:	48 89 e6             	mov    %rsp,%rsi
  400f75:	e8 40 08 00 00       	callq  4017ba <read_six_numbers>
  400f7a:	83 3c 24 01          	cmpl   $0x1,(%rsp)
  400f7e:	74 05                	je     400f85 <phase_2+0x19>
  400f80:	e8 d4 06 00 00       	callq  401659 <explode_bomb>
  400f85:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
  400f8a:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  400f8f:	8b 43 fc             	mov    -0x4(%rbx),%eax
  400f92:	01 c0                	add    %eax,%eax
  400f94:	39 03                	cmp    %eax,(%rbx)
  400f96:	74 05                	je     400f9d <phase_2+0x31>
  400f98:	e8 bc 06 00 00       	callq  401659 <explode_bomb>
  400f9d:	48 83 c3 04          	add    $0x4,%rbx
  400fa1:	48 39 eb             	cmp    %rbp,%rbx
  400fa4:	75 e9                	jne    400f8f <phase_2+0x23>
  400fa6:	48 83 c4 28          	add    $0x28,%rsp
  400faa:	5b                   	pop    %rbx
  400fab:	5d                   	pop    %rbp
  400fac:	c3                   	retq   

0000000000400fad <phase_3>:
  400fad:	48 83 ec 18          	sub    $0x18,%rsp
  400fb1:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  400fb6:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  400fbb:	be 9a 2b 40 00       	mov    $0x402b9a,%esi
  400fc0:	b8 00 00 00 00       	mov    $0x0,%eax
  400fc5:	e8 b6 fc ff ff       	callq  400c80 <__isoc99_sscanf@plt>
  400fca:	83 f8 01             	cmp    $0x1,%eax
  400fcd:	7f 05                	jg     400fd4 <phase_3+0x27>
  400fcf:	e8 85 06 00 00       	callq  401659 <explode_bomb>
  400fd4:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp)
  400fd9:	77 3c                	ja     401017 <phase_3+0x6a>
  400fdb:	8b 44 24 08          	mov    0x8(%rsp),%eax
  400fdf:	ff 24 c5 60 28 40 00 	jmpq   *0x402860(,%rax,8)
  400fe6:	b8 c4 00 00 00       	mov    $0xc4,%eax
  400feb:	eb 3b                	jmp    401028 <phase_3+0x7b>
  400fed:	b8 cf 02 00 00       	mov    $0x2cf,%eax
  400ff2:	eb 34                	jmp    401028 <phase_3+0x7b>
  400ff4:	b8 c8 02 00 00       	mov    $0x2c8,%eax
  400ff9:	eb 2d                	jmp    401028 <phase_3+0x7b>
  400ffb:	b8 21 02 00 00       	mov    $0x221,%eax
  401000:	eb 26                	jmp    401028 <phase_3+0x7b>
  401002:	b8 2d 02 00 00       	mov    $0x22d,%eax
  401007:	eb 1f                	jmp    401028 <phase_3+0x7b>
  401009:	b8 e5 00 00 00       	mov    $0xe5,%eax
  40100e:	eb 18                	jmp    401028 <phase_3+0x7b>
  401010:	b8 61 03 00 00       	mov    $0x361,%eax
  401015:	eb 11                	jmp    401028 <phase_3+0x7b>
  401017:	e8 3d 06 00 00       	callq  401659 <explode_bomb>
  40101c:	b8 00 00 00 00       	mov    $0x0,%eax
  401021:	eb 05                	jmp    401028 <phase_3+0x7b>
  401023:	b8 cb 01 00 00       	mov    $0x1cb,%eax
  401028:	3b 44 24 0c          	cmp    0xc(%rsp),%eax
  40102c:	74 05                	je     401033 <phase_3+0x86>
  40102e:	e8 26 06 00 00       	callq  401659 <explode_bomb>
  401033:	48 83 c4 18          	add    $0x18,%rsp
  401037:	c3                   	retq   

0000000000401038 <func4>:
  401038:	48 83 ec 08          	sub    $0x8,%rsp
  40103c:	89 d0                	mov    %edx,%eax
  40103e:	29 f0                	sub    %esi,%eax
  401040:	89 c1                	mov    %eax,%ecx
  401042:	c1 e9 1f             	shr    $0x1f,%ecx
  401045:	01 c8                	add    %ecx,%eax
  401047:	d1 f8                	sar    %eax
  401049:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  40104c:	39 f9                	cmp    %edi,%ecx
  40104e:	7e 0c                	jle    40105c <func4+0x24>
  401050:	8d 51 ff             	lea    -0x1(%rcx),%edx
  401053:	e8 e0 ff ff ff       	callq  401038 <func4>
  401058:	01 c0                	add    %eax,%eax
  40105a:	eb 15                	jmp    401071 <func4+0x39>
  40105c:	b8 00 00 00 00       	mov    $0x0,%eax
  401061:	39 f9                	cmp    %edi,%ecx
  401063:	7d 0c                	jge    401071 <func4+0x39>
  401065:	8d 71 01             	lea    0x1(%rcx),%esi
  401068:	e8 cb ff ff ff       	callq  401038 <func4>
  40106d:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401071:	48 83 c4 08          	add    $0x8,%rsp
  401075:	c3                   	retq   

0000000000401076 <phase_4>:
  401076:	48 83 ec 18          	sub    $0x18,%rsp
  40107a:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  40107f:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  401084:	be 9a 2b 40 00       	mov    $0x402b9a,%esi
  401089:	b8 00 00 00 00       	mov    $0x0,%eax
  40108e:	e8 ed fb ff ff       	callq  400c80 <__isoc99_sscanf@plt>
  401093:	83 f8 02             	cmp    $0x2,%eax
  401096:	75 0d                	jne    4010a5 <phase_4+0x2f>
  401098:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40109c:	85 c0                	test   %eax,%eax
  40109e:	78 05                	js     4010a5 <phase_4+0x2f>
  4010a0:	83 f8 0e             	cmp    $0xe,%eax
  4010a3:	7e 05                	jle    4010aa <phase_4+0x34>
  4010a5:	e8 af 05 00 00       	callq  401659 <explode_bomb>
  4010aa:	ba 0e 00 00 00       	mov    $0xe,%edx
  4010af:	be 00 00 00 00       	mov    $0x0,%esi
  4010b4:	8b 7c 24 08          	mov    0x8(%rsp),%edi
  4010b8:	e8 7b ff ff ff       	callq  401038 <func4>
  4010bd:	83 f8 07             	cmp    $0x7,%eax
  4010c0:	75 07                	jne    4010c9 <phase_4+0x53>
  4010c2:	83 7c 24 0c 07       	cmpl   $0x7,0xc(%rsp)
  4010c7:	74 05                	je     4010ce <phase_4+0x58>
  4010c9:	e8 8b 05 00 00       	callq  401659 <explode_bomb>
  4010ce:	48 83 c4 18          	add    $0x18,%rsp
  4010d2:	c3                   	retq   

00000000004010d3 <phase_5>:
  4010d3:	53                   	push   %rbx
  4010d4:	48 89 fb             	mov    %rdi,%rbx
  4010d7:	e8 5f 02 00 00       	callq  40133b <string_length>
  4010dc:	83 f8 06             	cmp    $0x6,%eax
  4010df:	74 05                	je     4010e6 <phase_5+0x13>
  4010e1:	e8 73 05 00 00       	callq  401659 <explode_bomb>
  4010e6:	b8 00 00 00 00       	mov    $0x0,%eax
  4010eb:	ba 00 00 00 00       	mov    $0x0,%edx
  4010f0:	0f be 0c 03          	movsbl (%rbx,%rax,1),%ecx
  4010f4:	83 e1 0f             	and    $0xf,%ecx
  4010f7:	03 14 8d a0 28 40 00 	add    0x4028a0(,%rcx,4),%edx
  4010fe:	48 83 c0 01          	add    $0x1,%rax
  401102:	48 83 f8 06          	cmp    $0x6,%rax
  401106:	75 e8                	jne    4010f0 <phase_5+0x1d>
  401108:	83 fa 31             	cmp    $0x31,%edx
  40110b:	74 05                	je     401112 <phase_5+0x3f>
  40110d:	e8 47 05 00 00       	callq  401659 <explode_bomb>
  401112:	5b                   	pop    %rbx
  401113:	c3                   	retq   

0000000000401114 <phase_6>:
  401114:	41 56                	push   %r14
  401116:	41 55                	push   %r13
  401118:	41 54                	push   %r12
  40111a:	55                   	push   %rbp
  40111b:	53                   	push   %rbx
  40111c:	48 83 ec 50          	sub    $0x50,%rsp
  401120:	48 8d 74 24 30       	lea    0x30(%rsp),%rsi
  401125:	e8 90 06 00 00       	callq  4017ba <read_six_numbers>
  40112a:	4c 8d 64 24 30       	lea    0x30(%rsp),%r12
  40112f:	4d 89 e5             	mov    %r12,%r13
  401132:	41 be 00 00 00 00    	mov    $0x0,%r14d
  401138:	4c 89 ed             	mov    %r13,%rbp
  40113b:	41 8b 45 00          	mov    0x0(%r13),%eax
  40113f:	83 e8 01             	sub    $0x1,%eax
  401142:	83 f8 05             	cmp    $0x5,%eax
  401145:	76 05                	jbe    40114c <phase_6+0x38>
  401147:	e8 0d 05 00 00       	callq  401659 <explode_bomb>
  40114c:	41 83 c6 01          	add    $0x1,%r14d
  401150:	41 83 fe 06          	cmp    $0x6,%r14d
  401154:	74 22                	je     401178 <phase_6+0x64>
  401156:	44 89 f3             	mov    %r14d,%ebx
  401159:	48 63 c3             	movslq %ebx,%rax
  40115c:	8b 54 84 30          	mov    0x30(%rsp,%rax,4),%edx
  401160:	39 55 00             	cmp    %edx,0x0(%rbp)
  401163:	75 05                	jne    40116a <phase_6+0x56>
  401165:	e8 ef 04 00 00       	callq  401659 <explode_bomb>
  40116a:	83 c3 01             	add    $0x1,%ebx
  40116d:	83 fb 05             	cmp    $0x5,%ebx
  401170:	7e e7                	jle    401159 <phase_6+0x45>
  401172:	49 83 c5 04          	add    $0x4,%r13
  401176:	eb c0                	jmp    401138 <phase_6+0x24>
  401178:	48 8d 4c 24 48       	lea    0x48(%rsp),%rcx
  40117d:	ba 07 00 00 00       	mov    $0x7,%edx
  401182:	89 d0                	mov    %edx,%eax
  401184:	41 2b 04 24          	sub    (%r12),%eax
  401188:	41 89 04 24          	mov    %eax,(%r12)
  40118c:	49 83 c4 04          	add    $0x4,%r12
  401190:	49 39 cc             	cmp    %rcx,%r12
  401193:	75 ed                	jne    401182 <phase_6+0x6e>
  401195:	be 00 00 00 00       	mov    $0x0,%esi
  40119a:	eb 19                	jmp    4011b5 <phase_6+0xa1>
  40119c:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  4011a0:	83 c0 01             	add    $0x1,%eax
  4011a3:	39 c8                	cmp    %ecx,%eax
  4011a5:	75 f5                	jne    40119c <phase_6+0x88>
  4011a7:	48 89 14 74          	mov    %rdx,(%rsp,%rsi,2)
  4011ab:	48 83 c6 04          	add    $0x4,%rsi
  4011af:	48 83 fe 18          	cmp    $0x18,%rsi
  4011b3:	74 15                	je     4011ca <phase_6+0xb6>
  4011b5:	8b 4c 34 30          	mov    0x30(%rsp,%rsi,1),%ecx
  4011b9:	b8 01 00 00 00       	mov    $0x1,%eax
  4011be:	ba 00 43 60 00       	mov    $0x604300,%edx
  4011c3:	83 f9 01             	cmp    $0x1,%ecx
  4011c6:	7f d4                	jg     40119c <phase_6+0x88>
  4011c8:	eb dd                	jmp    4011a7 <phase_6+0x93>
  4011ca:	48 8b 1c 24          	mov    (%rsp),%rbx
  4011ce:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  4011d3:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4011d7:	48 8b 54 24 10       	mov    0x10(%rsp),%rdx
  4011dc:	48 89 50 08          	mov    %rdx,0x8(%rax)
  4011e0:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4011e5:	48 89 42 08          	mov    %rax,0x8(%rdx)
  4011e9:	48 8b 54 24 20       	mov    0x20(%rsp),%rdx
  4011ee:	48 89 50 08          	mov    %rdx,0x8(%rax)
  4011f2:	48 8b 44 24 28       	mov    0x28(%rsp),%rax
  4011f7:	48 89 42 08          	mov    %rax,0x8(%rdx)
  4011fb:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  401202:	00 
  401203:	bd 05 00 00 00       	mov    $0x5,%ebp
  401208:	48 8b 43 08          	mov    0x8(%rbx),%rax
  40120c:	8b 10                	mov    (%rax),%edx
  40120e:	39 13                	cmp    %edx,(%rbx)
  401210:	7d 05                	jge    401217 <phase_6+0x103>
  401212:	e8 42 04 00 00       	callq  401659 <explode_bomb>
  401217:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  40121b:	83 ed 01             	sub    $0x1,%ebp
  40121e:	75 e8                	jne    401208 <phase_6+0xf4>
  401220:	48 83 c4 50          	add    $0x50,%rsp
  401224:	5b                   	pop    %rbx
  401225:	5d                   	pop    %rbp
  401226:	41 5c                	pop    %r12
  401228:	41 5d                	pop    %r13
  40122a:	41 5e                	pop    %r14
  40122c:	c3                   	retq   

000000000040122d <fun7>:
  40122d:	48 83 ec 08          	sub    $0x8,%rsp
  401231:	48 85 ff             	test   %rdi,%rdi
  401234:	74 2b                	je     401261 <fun7+0x34>
  401236:	8b 17                	mov    (%rdi),%edx
  401238:	39 f2                	cmp    %esi,%edx
  40123a:	7e 0d                	jle    401249 <fun7+0x1c>
  40123c:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  401240:	e8 e8 ff ff ff       	callq  40122d <fun7>
  401245:	01 c0                	add    %eax,%eax
  401247:	eb 1d                	jmp    401266 <fun7+0x39>
  401249:	b8 00 00 00 00       	mov    $0x0,%eax
  40124e:	39 f2                	cmp    %esi,%edx
  401250:	74 14                	je     401266 <fun7+0x39>
  401252:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  401256:	e8 d2 ff ff ff       	callq  40122d <fun7>
  40125b:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  40125f:	eb 05                	jmp    401266 <fun7+0x39>
  401261:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401266:	48 83 c4 08          	add    $0x8,%rsp
  40126a:	c3                   	retq   

000000000040126b <secret_phase>:
  40126b:	53                   	push   %rbx
  40126c:	e8 1e 04 00 00       	callq  40168f <read_line>
  401271:	ba 0a 00 00 00       	mov    $0xa,%edx
  401276:	be 00 00 00 00       	mov    $0x0,%esi
  40127b:	48 89 c7             	mov    %rax,%rdi
  40127e:	e8 dd f9 ff ff       	callq  400c60 <strtol@plt>
  401283:	89 c3                	mov    %eax,%ebx
  401285:	8d 43 ff             	lea    -0x1(%rbx),%eax
  401288:	3d e8 03 00 00       	cmp    $0x3e8,%eax
  40128d:	76 05                	jbe    401294 <secret_phase+0x29>
  40128f:	e8 c5 03 00 00       	callq  401659 <explode_bomb>
  401294:	89 de                	mov    %ebx,%esi
  401296:	bf 20 41 60 00       	mov    $0x604120,%edi
  40129b:	e8 8d ff ff ff       	callq  40122d <fun7>
  4012a0:	83 f8 03             	cmp    $0x3,%eax
  4012a3:	74 05                	je     4012aa <secret_phase+0x3f>
  4012a5:	e8 af 03 00 00       	callq  401659 <explode_bomb>
  4012aa:	bf 28 28 40 00       	mov    $0x402828,%edi
  4012af:	e8 ec f8 ff ff       	callq  400ba0 <puts@plt>
  4012b4:	e8 43 05 00 00       	callq  4017fc <phase_defused>
  4012b9:	5b                   	pop    %rbx
  4012ba:	c3                   	retq   
  4012bb:	90                   	nop
  4012bc:	90                   	nop
  4012bd:	90                   	nop
  4012be:	90                   	nop
  4012bf:	90                   	nop

00000000004012c0 <sig_handler>:
  4012c0:	48 83 ec 08          	sub    $0x8,%rsp
  4012c4:	bf e0 28 40 00       	mov    $0x4028e0,%edi
  4012c9:	e8 d2 f8 ff ff       	callq  400ba0 <puts@plt>
  4012ce:	bf 03 00 00 00       	mov    $0x3,%edi
  4012d3:	e8 18 fa ff ff       	callq  400cf0 <sleep@plt>
  4012d8:	be cf 2a 40 00       	mov    $0x402acf,%esi
  4012dd:	bf 01 00 00 00       	mov    $0x1,%edi
  4012e2:	b8 00 00 00 00       	mov    $0x0,%eax
  4012e7:	e8 a4 f9 ff ff       	callq  400c90 <__printf_chk@plt>
  4012ec:	48 8b 3d 0d 43 20 00 	mov    0x20430d(%rip),%rdi        # 605600 <__bss_start>
  4012f3:	e8 78 f9 ff ff       	callq  400c70 <fflush@plt>
  4012f8:	bf 01 00 00 00       	mov    $0x1,%edi
  4012fd:	e8 ee f9 ff ff       	callq  400cf0 <sleep@plt>
  401302:	bf d7 2a 40 00       	mov    $0x402ad7,%edi
  401307:	e8 94 f8 ff ff       	callq  400ba0 <puts@plt>
  40130c:	bf 10 00 00 00       	mov    $0x10,%edi
  401311:	e8 aa f9 ff ff       	callq  400cc0 <exit@plt>

0000000000401316 <invalid_phase>:
  401316:	48 83 ec 08          	sub    $0x8,%rsp
  40131a:	48 89 fa             	mov    %rdi,%rdx
  40131d:	be df 2a 40 00       	mov    $0x402adf,%esi
  401322:	bf 01 00 00 00       	mov    $0x1,%edi
  401327:	b8 00 00 00 00       	mov    $0x0,%eax
  40132c:	e8 5f f9 ff ff       	callq  400c90 <__printf_chk@plt>
  401331:	bf 08 00 00 00       	mov    $0x8,%edi
  401336:	e8 85 f9 ff ff       	callq  400cc0 <exit@plt>

000000000040133b <string_length>:
  40133b:	b8 00 00 00 00       	mov    $0x0,%eax
  401340:	80 3f 00             	cmpb   $0x0,(%rdi)
  401343:	74 10                	je     401355 <string_length+0x1a>
  401345:	48 89 fa             	mov    %rdi,%rdx
  401348:	48 83 c2 01          	add    $0x1,%rdx
  40134c:	89 d0                	mov    %edx,%eax
  40134e:	29 f8                	sub    %edi,%eax
  401350:	80 3a 00             	cmpb   $0x0,(%rdx)
  401353:	75 f3                	jne    401348 <string_length+0xd>
  401355:	f3 c3                	repz retq 

0000000000401357 <strings_not_equal>:
  401357:	48 89 5c 24 e8       	mov    %rbx,-0x18(%rsp)
  40135c:	48 89 6c 24 f0       	mov    %rbp,-0x10(%rsp)
  401361:	4c 89 64 24 f8       	mov    %r12,-0x8(%rsp)
  401366:	48 83 ec 18          	sub    $0x18,%rsp
  40136a:	48 89 fb             	mov    %rdi,%rbx
  40136d:	48 89 f5             	mov    %rsi,%rbp
  401370:	e8 c6 ff ff ff       	callq  40133b <string_length>
  401375:	41 89 c4             	mov    %eax,%r12d
  401378:	48 89 ef             	mov    %rbp,%rdi
  40137b:	e8 bb ff ff ff       	callq  40133b <string_length>
  401380:	ba 01 00 00 00       	mov    $0x1,%edx
  401385:	41 39 c4             	cmp    %eax,%r12d
  401388:	75 36                	jne    4013c0 <strings_not_equal+0x69>
  40138a:	0f b6 03             	movzbl (%rbx),%eax
  40138d:	b2 00                	mov    $0x0,%dl
  40138f:	84 c0                	test   %al,%al
  401391:	74 2d                	je     4013c0 <strings_not_equal+0x69>
  401393:	b2 01                	mov    $0x1,%dl
  401395:	3a 45 00             	cmp    0x0(%rbp),%al
  401398:	75 26                	jne    4013c0 <strings_not_equal+0x69>
  40139a:	b8 00 00 00 00       	mov    $0x0,%eax
  40139f:	eb 0a                	jmp    4013ab <strings_not_equal+0x54>
  4013a1:	48 83 c0 01          	add    $0x1,%rax
  4013a5:	3a 54 05 00          	cmp    0x0(%rbp,%rax,1),%dl
  4013a9:	75 10                	jne    4013bb <strings_not_equal+0x64>
  4013ab:	0f b6 54 03 01       	movzbl 0x1(%rbx,%rax,1),%edx
  4013b0:	84 d2                	test   %dl,%dl
  4013b2:	75 ed                	jne    4013a1 <strings_not_equal+0x4a>
  4013b4:	ba 00 00 00 00       	mov    $0x0,%edx
  4013b9:	eb 05                	jmp    4013c0 <strings_not_equal+0x69>
  4013bb:	ba 01 00 00 00       	mov    $0x1,%edx
  4013c0:	89 d0                	mov    %edx,%eax
  4013c2:	48 8b 1c 24          	mov    (%rsp),%rbx
  4013c6:	48 8b 6c 24 08       	mov    0x8(%rsp),%rbp
  4013cb:	4c 8b 64 24 10       	mov    0x10(%rsp),%r12
  4013d0:	48 83 c4 18          	add    $0x18,%rsp
  4013d4:	c3                   	retq   

00000000004013d5 <initialize_bomb>:
  4013d5:	53                   	push   %rbx
  4013d6:	48 81 ec 50 20 00 00 	sub    $0x2050,%rsp
  4013dd:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4013e4:	00 00 
  4013e6:	48 89 84 24 48 20 00 	mov    %rax,0x2048(%rsp)
  4013ed:	00 
  4013ee:	31 c0                	xor    %eax,%eax
  4013f0:	be c0 12 40 00       	mov    $0x4012c0,%esi
  4013f5:	bf 02 00 00 00       	mov    $0x2,%edi
  4013fa:	e8 21 f8 ff ff       	callq  400c20 <signal@plt>
  4013ff:	be 40 00 00 00       	mov    $0x40,%esi
  401404:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
  40140b:	00 
  40140c:	e8 9f f8 ff ff       	callq  400cb0 <gethostname@plt>
  401411:	85 c0                	test   %eax,%eax
  401413:	75 13                	jne    401428 <initialize_bomb+0x53>
  401415:	48 8b 3d 64 3f 20 00 	mov    0x203f64(%rip),%rdi        # 605380 <host_table>
  40141c:	bb 88 53 60 00       	mov    $0x605388,%ebx
  401421:	48 85 ff             	test   %rdi,%rdi
  401424:	75 16                	jne    40143c <initialize_bomb+0x67>
  401426:	eb 61                	jmp    401489 <initialize_bomb+0xb4>
  401428:	bf 18 29 40 00       	mov    $0x402918,%edi
  40142d:	e8 6e f7 ff ff       	callq  400ba0 <puts@plt>
  401432:	bf 08 00 00 00       	mov    $0x8,%edi
  401437:	e8 84 f8 ff ff       	callq  400cc0 <exit@plt>
  40143c:	48 8d b4 24 00 20 00 	lea    0x2000(%rsp),%rsi
  401443:	00 
  401444:	e8 27 f7 ff ff       	callq  400b70 <strcasecmp@plt>
  401449:	85 c0                	test   %eax,%eax
  40144b:	74 0f                	je     40145c <initialize_bomb+0x87>
  40144d:	48 83 c3 08          	add    $0x8,%rbx
  401451:	48 8b 7b f8          	mov    -0x8(%rbx),%rdi
  401455:	48 85 ff             	test   %rdi,%rdi
  401458:	75 e2                	jne    40143c <initialize_bomb+0x67>
  40145a:	eb 2d                	jmp    401489 <initialize_bomb+0xb4>
  40145c:	48 89 e7             	mov    %rsp,%rdi
  40145f:	e8 de 0e 00 00       	callq  402342 <init_driver>
  401464:	85 c0                	test   %eax,%eax
  401466:	79 35                	jns    40149d <initialize_bomb+0xc8>
  401468:	48 89 e2             	mov    %rsp,%rdx
  40146b:	be f0 2a 40 00       	mov    $0x402af0,%esi
  401470:	bf 01 00 00 00       	mov    $0x1,%edi
  401475:	b8 00 00 00 00       	mov    $0x0,%eax
  40147a:	e8 11 f8 ff ff       	callq  400c90 <__printf_chk@plt>
  40147f:	bf 08 00 00 00       	mov    $0x8,%edi
  401484:	e8 37 f8 ff ff       	callq  400cc0 <exit@plt>
  401489:	bf 50 29 40 00       	mov    $0x402950,%edi
  40148e:	e8 0d f7 ff ff       	callq  400ba0 <puts@plt>
  401493:	bf 08 00 00 00       	mov    $0x8,%edi
  401498:	e8 23 f8 ff ff       	callq  400cc0 <exit@plt>
  40149d:	48 8b 84 24 48 20 00 	mov    0x2048(%rsp),%rax
  4014a4:	00 
  4014a5:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4014ac:	00 00 
  4014ae:	74 05                	je     4014b5 <initialize_bomb+0xe0>
  4014b0:	e8 0b f7 ff ff       	callq  400bc0 <__stack_chk_fail@plt>
  4014b5:	48 81 c4 50 20 00 00 	add    $0x2050,%rsp
  4014bc:	5b                   	pop    %rbx
  4014bd:	c3                   	retq   

00000000004014be <initialize_bomb_solve>:
  4014be:	f3 c3                	repz retq 

00000000004014c0 <blank_line>:
  4014c0:	55                   	push   %rbp
  4014c1:	53                   	push   %rbx
  4014c2:	48 83 ec 08          	sub    $0x8,%rsp
  4014c6:	48 89 fd             	mov    %rdi,%rbp
  4014c9:	eb 17                	jmp    4014e2 <blank_line+0x22>
  4014cb:	e8 30 f8 ff ff       	callq  400d00 <__ctype_b_loc@plt>
  4014d0:	48 83 c5 01          	add    $0x1,%rbp
  4014d4:	48 0f be db          	movsbq %bl,%rbx
  4014d8:	48 8b 00             	mov    (%rax),%rax
  4014db:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
  4014e0:	74 0f                	je     4014f1 <blank_line+0x31>
  4014e2:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
  4014e6:	84 db                	test   %bl,%bl
  4014e8:	75 e1                	jne    4014cb <blank_line+0xb>
  4014ea:	b8 01 00 00 00       	mov    $0x1,%eax
  4014ef:	eb 05                	jmp    4014f6 <blank_line+0x36>
  4014f1:	b8 00 00 00 00       	mov    $0x0,%eax
  4014f6:	48 83 c4 08          	add    $0x8,%rsp
  4014fa:	5b                   	pop    %rbx
  4014fb:	5d                   	pop    %rbp
  4014fc:	c3                   	retq   

00000000004014fd <skip>:
  4014fd:	53                   	push   %rbx
  4014fe:	48 63 05 23 41 20 00 	movslq 0x204123(%rip),%rax        # 605628 <num_input_strings>
  401505:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
  401509:	48 c1 e7 04          	shl    $0x4,%rdi
  40150d:	48 81 c7 40 56 60 00 	add    $0x605640,%rdi
  401514:	48 8b 15 15 41 20 00 	mov    0x204115(%rip),%rdx        # 605630 <infile>
  40151b:	be 50 00 00 00       	mov    $0x50,%esi
  401520:	e8 eb f6 ff ff       	callq  400c10 <fgets@plt>
  401525:	48 89 c3             	mov    %rax,%rbx
  401528:	48 85 c0             	test   %rax,%rax
  40152b:	74 0c                	je     401539 <skip+0x3c>
  40152d:	48 89 c7             	mov    %rax,%rdi
  401530:	e8 8b ff ff ff       	callq  4014c0 <blank_line>
  401535:	85 c0                	test   %eax,%eax
  401537:	75 c5                	jne    4014fe <skip+0x1>
  401539:	48 89 d8             	mov    %rbx,%rax
  40153c:	5b                   	pop    %rbx
  40153d:	c3                   	retq   

000000000040153e <send_msg>:
  40153e:	48 81 ec 38 40 00 00 	sub    $0x4038,%rsp
  401545:	41 89 f8             	mov    %edi,%r8d
  401548:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40154f:	00 00 
  401551:	48 89 84 24 28 40 00 	mov    %rax,0x4028(%rsp)
  401558:	00 
  401559:	31 c0                	xor    %eax,%eax
  40155b:	8b 15 c7 40 20 00    	mov    0x2040c7(%rip),%edx        # 605628 <num_input_strings>
  401561:	48 63 c2             	movslq %edx,%rax
  401564:	48 8d 74 80 fb       	lea    -0x5(%rax,%rax,4),%rsi
  401569:	48 c1 e6 04          	shl    $0x4,%rsi
  40156d:	48 81 c6 40 56 60 00 	add    $0x605640,%rsi
  401574:	48 89 f7             	mov    %rsi,%rdi
  401577:	b8 00 00 00 00       	mov    $0x0,%eax
  40157c:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401583:	f2 ae                	repnz scas %es:(%rdi),%al
  401585:	48 f7 d1             	not    %rcx
  401588:	48 83 c1 63          	add    $0x63,%rcx
  40158c:	48 81 f9 00 20 00 00 	cmp    $0x2000,%rcx
  401593:	76 19                	jbe    4015ae <send_msg+0x70>
  401595:	be 88 29 40 00       	mov    $0x402988,%esi
  40159a:	bf 01 00 00 00       	mov    $0x1,%edi
  40159f:	e8 ec f6 ff ff       	callq  400c90 <__printf_chk@plt>
  4015a4:	bf 08 00 00 00       	mov    $0x8,%edi
  4015a9:	e8 12 f7 ff ff       	callq  400cc0 <exit@plt>
  4015ae:	45 85 c0             	test   %r8d,%r8d
  4015b1:	b8 0a 2b 40 00       	mov    $0x402b0a,%eax
  4015b6:	b9 12 2b 40 00       	mov    $0x402b12,%ecx
  4015bb:	48 0f 44 c1          	cmove  %rcx,%rax
  4015bf:	48 89 74 24 10       	mov    %rsi,0x10(%rsp)
  4015c4:	89 54 24 08          	mov    %edx,0x8(%rsp)
  4015c8:	48 89 04 24          	mov    %rax,(%rsp)
  4015cc:	41 b9 60 4b 60 00    	mov    $0x604b60,%r9d
  4015d2:	44 8b 05 87 3d 20 00 	mov    0x203d87(%rip),%r8d        # 605360 <bomb_id>
  4015d9:	b9 1b 2b 40 00       	mov    $0x402b1b,%ecx
  4015de:	ba 00 20 00 00       	mov    $0x2000,%edx
  4015e3:	be 01 00 00 00       	mov    $0x1,%esi
  4015e8:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  4015ed:	b8 00 00 00 00       	mov    $0x0,%eax
  4015f2:	e8 19 f7 ff ff       	callq  400d10 <__sprintf_chk@plt>
  4015f7:	4c 8d 8c 24 20 20 00 	lea    0x2020(%rsp),%r9
  4015fe:	00 
  4015ff:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401605:	48 8d 4c 24 20       	lea    0x20(%rsp),%rcx
  40160a:	ba 60 43 60 00       	mov    $0x604360,%edx
  40160f:	be 60 47 60 00       	mov    $0x604760,%esi
  401614:	bf 60 4f 60 00       	mov    $0x604f60,%edi
  401619:	e8 17 0f 00 00       	callq  402535 <driver_post>
  40161e:	85 c0                	test   %eax,%eax
  401620:	79 17                	jns    401639 <send_msg+0xfb>
  401622:	48 8d bc 24 20 20 00 	lea    0x2020(%rsp),%rdi
  401629:	00 
  40162a:	e8 71 f5 ff ff       	callq  400ba0 <puts@plt>
  40162f:	bf 00 00 00 00       	mov    $0x0,%edi
  401634:	e8 87 f6 ff ff       	callq  400cc0 <exit@plt>
  401639:	48 8b 84 24 28 40 00 	mov    0x4028(%rsp),%rax
  401640:	00 
  401641:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401648:	00 00 
  40164a:	74 05                	je     401651 <send_msg+0x113>
  40164c:	e8 6f f5 ff ff       	callq  400bc0 <__stack_chk_fail@plt>
  401651:	48 81 c4 38 40 00 00 	add    $0x4038,%rsp
  401658:	c3                   	retq   

0000000000401659 <explode_bomb>:
  401659:	48 83 ec 08          	sub    $0x8,%rsp
  40165d:	bf 2a 2b 40 00       	mov    $0x402b2a,%edi
  401662:	e8 39 f5 ff ff       	callq  400ba0 <puts@plt>
  401667:	bf 33 2b 40 00       	mov    $0x402b33,%edi
  40166c:	e8 2f f5 ff ff       	callq  400ba0 <puts@plt>
  401671:	bf 00 00 00 00       	mov    $0x0,%edi
  401676:	e8 c3 fe ff ff       	callq  40153e <send_msg>
  40167b:	bf b0 29 40 00       	mov    $0x4029b0,%edi
  401680:	e8 1b f5 ff ff       	callq  400ba0 <puts@plt>
  401685:	bf 08 00 00 00       	mov    $0x8,%edi
  40168a:	e8 31 f6 ff ff       	callq  400cc0 <exit@plt>

000000000040168f <read_line>:
  40168f:	48 83 ec 08          	sub    $0x8,%rsp
  401693:	b8 00 00 00 00       	mov    $0x0,%eax
  401698:	e8 60 fe ff ff       	callq  4014fd <skip>
  40169d:	48 85 c0             	test   %rax,%rax
  4016a0:	75 6e                	jne    401710 <read_line+0x81>
  4016a2:	48 8b 05 5f 3f 20 00 	mov    0x203f5f(%rip),%rax        # 605608 <stdin@@GLIBC_2.2.5>
  4016a9:	48 39 05 80 3f 20 00 	cmp    %rax,0x203f80(%rip)        # 605630 <infile>
  4016b0:	75 14                	jne    4016c6 <read_line+0x37>
  4016b2:	bf 4a 2b 40 00       	mov    $0x402b4a,%edi
  4016b7:	e8 e4 f4 ff ff       	callq  400ba0 <puts@plt>
  4016bc:	bf 08 00 00 00       	mov    $0x8,%edi
  4016c1:	e8 fa f5 ff ff       	callq  400cc0 <exit@plt>
  4016c6:	bf 68 2b 40 00       	mov    $0x402b68,%edi
  4016cb:	e8 90 f4 ff ff       	callq  400b60 <getenv@plt>
  4016d0:	48 85 c0             	test   %rax,%rax
  4016d3:	74 0a                	je     4016df <read_line+0x50>
  4016d5:	bf 00 00 00 00       	mov    $0x0,%edi
  4016da:	e8 e1 f5 ff ff       	callq  400cc0 <exit@plt>
  4016df:	48 8b 05 22 3f 20 00 	mov    0x203f22(%rip),%rax        # 605608 <stdin@@GLIBC_2.2.5>
  4016e6:	48 89 05 43 3f 20 00 	mov    %rax,0x203f43(%rip)        # 605630 <infile>
  4016ed:	b8 00 00 00 00       	mov    $0x0,%eax
  4016f2:	e8 06 fe ff ff       	callq  4014fd <skip>
  4016f7:	48 85 c0             	test   %rax,%rax
  4016fa:	75 14                	jne    401710 <read_line+0x81>
  4016fc:	bf 4a 2b 40 00       	mov    $0x402b4a,%edi
  401701:	e8 9a f4 ff ff       	callq  400ba0 <puts@plt>
  401706:	bf 00 00 00 00       	mov    $0x0,%edi
  40170b:	e8 b0 f5 ff ff       	callq  400cc0 <exit@plt>
  401710:	8b 15 12 3f 20 00    	mov    0x203f12(%rip),%edx        # 605628 <num_input_strings>
  401716:	48 63 c2             	movslq %edx,%rax
  401719:	48 8d 34 80          	lea    (%rax,%rax,4),%rsi
  40171d:	48 c1 e6 04          	shl    $0x4,%rsi
  401721:	48 81 c6 40 56 60 00 	add    $0x605640,%rsi
  401728:	48 89 f7             	mov    %rsi,%rdi
  40172b:	b8 00 00 00 00       	mov    $0x0,%eax
  401730:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401737:	f2 ae                	repnz scas %es:(%rdi),%al
  401739:	48 f7 d1             	not    %rcx
  40173c:	83 e9 01             	sub    $0x1,%ecx
  40173f:	83 f9 4e             	cmp    $0x4e,%ecx
  401742:	7e 4c                	jle    401790 <read_line+0x101>
  401744:	bf 73 2b 40 00       	mov    $0x402b73,%edi
  401749:	e8 52 f4 ff ff       	callq  400ba0 <puts@plt>
  40174e:	8b 05 d4 3e 20 00    	mov    0x203ed4(%rip),%eax        # 605628 <num_input_strings>
  401754:	8d 50 01             	lea    0x1(%rax),%edx
  401757:	89 15 cb 3e 20 00    	mov    %edx,0x203ecb(%rip)        # 605628 <num_input_strings>
  40175d:	48 98                	cltq   
  40175f:	48 6b c0 50          	imul   $0x50,%rax,%rax
  401763:	c7 80 40 56 60 00 2a 	movl   $0x742a2a2a,0x605640(%rax)
  40176a:	2a 2a 74 
  40176d:	c7 80 44 56 60 00 72 	movl   $0x636e7572,0x605644(%rax)
  401774:	75 6e 63 
  401777:	c7 80 48 56 60 00 61 	movl   $0x64657461,0x605648(%rax)
  40177e:	74 65 64 
  401781:	c7 80 4c 56 60 00 2a 	movl   $0x2a2a2a,0x60564c(%rax)
  401788:	2a 2a 00 
  40178b:	e8 c9 fe ff ff       	callq  401659 <explode_bomb>
  401790:	83 e9 01             	sub    $0x1,%ecx
  401793:	48 63 c9             	movslq %ecx,%rcx
  401796:	48 63 c2             	movslq %edx,%rax
  401799:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
  40179d:	48 c1 e0 04          	shl    $0x4,%rax
  4017a1:	c6 84 01 40 56 60 00 	movb   $0x0,0x605640(%rcx,%rax,1)
  4017a8:	00 
  4017a9:	83 c2 01             	add    $0x1,%edx
  4017ac:	89 15 76 3e 20 00    	mov    %edx,0x203e76(%rip)        # 605628 <num_input_strings>
  4017b2:	48 89 f0             	mov    %rsi,%rax
  4017b5:	48 83 c4 08          	add    $0x8,%rsp
  4017b9:	c3                   	retq   

00000000004017ba <read_six_numbers>:
  4017ba:	48 83 ec 18          	sub    $0x18,%rsp
  4017be:	48 89 f2             	mov    %rsi,%rdx
  4017c1:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  4017c5:	48 8d 46 14          	lea    0x14(%rsi),%rax
  4017c9:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4017ce:	48 8d 46 10          	lea    0x10(%rsi),%rax
  4017d2:	48 89 04 24          	mov    %rax,(%rsp)
  4017d6:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  4017da:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  4017de:	be 8e 2b 40 00       	mov    $0x402b8e,%esi
  4017e3:	b8 00 00 00 00       	mov    $0x0,%eax
  4017e8:	e8 93 f4 ff ff       	callq  400c80 <__isoc99_sscanf@plt>
  4017ed:	83 f8 05             	cmp    $0x5,%eax
  4017f0:	7f 05                	jg     4017f7 <read_six_numbers+0x3d>
  4017f2:	e8 62 fe ff ff       	callq  401659 <explode_bomb>
  4017f7:	48 83 c4 18          	add    $0x18,%rsp
  4017fb:	c3                   	retq   

00000000004017fc <phase_defused>:
  4017fc:	48 83 ec 78          	sub    $0x78,%rsp
  401800:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401807:	00 00 
  401809:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
  40180e:	31 c0                	xor    %eax,%eax
  401810:	bf 01 00 00 00       	mov    $0x1,%edi
  401815:	e8 24 fd ff ff       	callq  40153e <send_msg>
  40181a:	83 3d 07 3e 20 00 06 	cmpl   $0x6,0x203e07(%rip)        # 605628 <num_input_strings>
  401821:	75 6d                	jne    401890 <phase_defused+0x94>
  401823:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
  401828:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  40182d:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  401832:	be a0 2b 40 00       	mov    $0x402ba0,%esi
  401837:	bf 30 57 60 00       	mov    $0x605730,%edi
  40183c:	b8 00 00 00 00       	mov    $0x0,%eax
  401841:	e8 3a f4 ff ff       	callq  400c80 <__isoc99_sscanf@plt>
  401846:	83 f8 03             	cmp    $0x3,%eax
  401849:	75 31                	jne    40187c <phase_defused+0x80>
  40184b:	be a9 2b 40 00       	mov    $0x402ba9,%esi
  401850:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  401855:	e8 fd fa ff ff       	callq  401357 <strings_not_equal>
  40185a:	85 c0                	test   %eax,%eax
  40185c:	75 1e                	jne    40187c <phase_defused+0x80>
  40185e:	bf d8 29 40 00       	mov    $0x4029d8,%edi
  401863:	e8 38 f3 ff ff       	callq  400ba0 <puts@plt>
  401868:	bf 00 2a 40 00       	mov    $0x402a00,%edi
  40186d:	e8 2e f3 ff ff       	callq  400ba0 <puts@plt>
  401872:	b8 00 00 00 00       	mov    $0x0,%eax
  401877:	e8 ef f9 ff ff       	callq  40126b <secret_phase>
  40187c:	bf 38 2a 40 00       	mov    $0x402a38,%edi
  401881:	e8 1a f3 ff ff       	callq  400ba0 <puts@plt>
  401886:	bf 68 2a 40 00       	mov    $0x402a68,%edi
  40188b:	e8 10 f3 ff ff       	callq  400ba0 <puts@plt>
  401890:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
  401895:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  40189c:	00 00 
  40189e:	74 05                	je     4018a5 <phase_defused+0xa9>
  4018a0:	e8 1b f3 ff ff       	callq  400bc0 <__stack_chk_fail@plt>
  4018a5:	48 83 c4 78          	add    $0x78,%rsp
  4018a9:	c3                   	retq   
  4018aa:	90                   	nop
  4018ab:	90                   	nop
  4018ac:	90                   	nop
  4018ad:	90                   	nop
  4018ae:	90                   	nop
  4018af:	90                   	nop

00000000004018b0 <rio_readlineb>:
  4018b0:	41 57                	push   %r15
  4018b2:	41 56                	push   %r14
  4018b4:	41 55                	push   %r13
  4018b6:	41 54                	push   %r12
  4018b8:	55                   	push   %rbp
  4018b9:	53                   	push   %rbx
  4018ba:	48 83 ec 28          	sub    $0x28,%rsp
  4018be:	48 89 fd             	mov    %rdi,%rbp
  4018c1:	48 89 54 24 08       	mov    %rdx,0x8(%rsp)
  4018c6:	49 89 f7             	mov    %rsi,%r15
  4018c9:	41 be 01 00 00 00    	mov    $0x1,%r14d
  4018cf:	4c 8d 6f 10          	lea    0x10(%rdi),%r13
  4018d3:	48 83 fa 01          	cmp    $0x1,%rdx
  4018d7:	77 38                	ja     401911 <rio_readlineb+0x61>
  4018d9:	e9 a7 00 00 00       	jmpq   401985 <rio_readlineb+0xd5>
  4018de:	ba 00 20 00 00       	mov    $0x2000,%edx
  4018e3:	4c 89 ee             	mov    %r13,%rsi
  4018e6:	8b 7d 00             	mov    0x0(%rbp),%edi
  4018e9:	e8 02 f3 ff ff       	callq  400bf0 <read@plt>
  4018ee:	89 45 04             	mov    %eax,0x4(%rbp)
  4018f1:	85 c0                	test   %eax,%eax
  4018f3:	79 10                	jns    401905 <rio_readlineb+0x55>
  4018f5:	e8 86 f2 ff ff       	callq  400b80 <__errno_location@plt>
  4018fa:	83 38 04             	cmpl   $0x4,(%rax)
  4018fd:	74 12                	je     401911 <rio_readlineb+0x61>
  4018ff:	90                   	nop
  401900:	e9 99 00 00 00       	jmpq   40199e <rio_readlineb+0xee>
  401905:	85 c0                	test   %eax,%eax
  401907:	0f 84 9a 00 00 00    	je     4019a7 <rio_readlineb+0xf7>
  40190d:	4c 89 6d 08          	mov    %r13,0x8(%rbp)
  401911:	44 8b 65 04          	mov    0x4(%rbp),%r12d
  401915:	45 85 e4             	test   %r12d,%r12d
  401918:	7e c4                	jle    4018de <rio_readlineb+0x2e>
  40191a:	45 85 e4             	test   %r12d,%r12d
  40191d:	0f 85 8e 00 00 00    	jne    4019b1 <rio_readlineb+0x101>
  401923:	49 63 dc             	movslq %r12d,%rbx
  401926:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  40192a:	b9 01 00 00 00       	mov    $0x1,%ecx
  40192f:	48 89 da             	mov    %rbx,%rdx
  401932:	48 8d 7c 24 1f       	lea    0x1f(%rsp),%rdi
  401937:	e8 14 f3 ff ff       	callq  400c50 <__memcpy_chk@plt>
  40193c:	48 01 5d 08          	add    %rbx,0x8(%rbp)
  401940:	44 29 65 04          	sub    %r12d,0x4(%rbp)
  401944:	44 89 e0             	mov    %r12d,%eax
  401947:	41 83 fc 01          	cmp    $0x1,%r12d
  40194b:	75 12                	jne    40195f <rio_readlineb+0xaf>
  40194d:	0f b6 44 24 1f       	movzbl 0x1f(%rsp),%eax
  401952:	41 88 07             	mov    %al,(%r15)
  401955:	49 83 c7 01          	add    $0x1,%r15
  401959:	3c 0a                	cmp    $0xa,%al
  40195b:	75 1d                	jne    40197a <rio_readlineb+0xca>
  40195d:	eb 26                	jmp    401985 <rio_readlineb+0xd5>
  40195f:	4c 89 f2             	mov    %r14,%rdx
  401962:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401969:	85 c0                	test   %eax,%eax
  40196b:	75 1f                	jne    40198c <rio_readlineb+0xdc>
  40196d:	b9 00 00 00 00       	mov    $0x0,%ecx
  401972:	48 83 fa 01          	cmp    $0x1,%rdx
  401976:	75 0d                	jne    401985 <rio_readlineb+0xd5>
  401978:	eb 12                	jmp    40198c <rio_readlineb+0xdc>
  40197a:	49 83 c6 01          	add    $0x1,%r14
  40197e:	4c 3b 74 24 08       	cmp    0x8(%rsp),%r14
  401983:	75 8c                	jne    401911 <rio_readlineb+0x61>
  401985:	41 c6 07 00          	movb   $0x0,(%r15)
  401989:	4c 89 f1             	mov    %r14,%rcx
  40198c:	48 89 c8             	mov    %rcx,%rax
  40198f:	48 83 c4 28          	add    $0x28,%rsp
  401993:	5b                   	pop    %rbx
  401994:	5d                   	pop    %rbp
  401995:	41 5c                	pop    %r12
  401997:	41 5d                	pop    %r13
  401999:	41 5e                	pop    %r14
  40199b:	41 5f                	pop    %r15
  40199d:	c3                   	retq   
  40199e:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  4019a5:	eb 05                	jmp    4019ac <rio_readlineb+0xfc>
  4019a7:	b8 00 00 00 00       	mov    $0x0,%eax
  4019ac:	4c 89 f2             	mov    %r14,%rdx
  4019af:	eb b1                	jmp    401962 <rio_readlineb+0xb2>
  4019b1:	48 8b 45 08          	mov    0x8(%rbp),%rax
  4019b5:	0f b6 00             	movzbl (%rax),%eax
  4019b8:	88 44 24 1f          	mov    %al,0x1f(%rsp)
  4019bc:	48 83 45 08 01       	addq   $0x1,0x8(%rbp)
  4019c1:	83 6d 04 01          	subl   $0x1,0x4(%rbp)
  4019c5:	eb 86                	jmp    40194d <rio_readlineb+0x9d>

00000000004019c7 <sigalrm_handler>:
  4019c7:	48 83 ec 08          	sub    $0x8,%rsp
  4019cb:	b9 00 00 00 00       	mov    $0x0,%ecx
  4019d0:	ba e8 2c 40 00       	mov    $0x402ce8,%edx
  4019d5:	be 01 00 00 00       	mov    $0x1,%esi
  4019da:	48 8b 3d 2f 3c 20 00 	mov    0x203c2f(%rip),%rdi        # 605610 <stderr@@GLIBC_2.2.5>
  4019e1:	b8 00 00 00 00       	mov    $0x0,%eax
  4019e6:	e8 f5 f2 ff ff       	callq  400ce0 <__fprintf_chk@plt>
  4019eb:	bf 01 00 00 00       	mov    $0x1,%edi
  4019f0:	e8 cb f2 ff ff       	callq  400cc0 <exit@plt>

00000000004019f5 <submitr>:
  4019f5:	41 57                	push   %r15
  4019f7:	41 56                	push   %r14
  4019f9:	41 55                	push   %r13
  4019fb:	41 54                	push   %r12
  4019fd:	55                   	push   %rbp
  4019fe:	53                   	push   %rbx
  4019ff:	48 81 ec 88 a0 00 00 	sub    $0xa088,%rsp
  401a06:	49 89 ff             	mov    %rdi,%r15
  401a09:	89 f5                	mov    %esi,%ebp
  401a0b:	48 89 54 24 28       	mov    %rdx,0x28(%rsp)
  401a10:	48 89 4c 24 30       	mov    %rcx,0x30(%rsp)
  401a15:	4c 89 44 24 38       	mov    %r8,0x38(%rsp)
  401a1a:	4c 89 cb             	mov    %r9,%rbx
  401a1d:	4c 8b b4 24 c0 a0 00 	mov    0xa0c0(%rsp),%r14
  401a24:	00 
  401a25:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401a2c:	00 00 
  401a2e:	48 89 84 24 78 a0 00 	mov    %rax,0xa078(%rsp)
  401a35:	00 
  401a36:	31 c0                	xor    %eax,%eax
  401a38:	c7 44 24 4c 00 00 00 	movl   $0x0,0x4c(%rsp)
  401a3f:	00 
  401a40:	ba 00 00 00 00       	mov    $0x0,%edx
  401a45:	be 01 00 00 00       	mov    $0x1,%esi
  401a4a:	bf 02 00 00 00       	mov    $0x2,%edi
  401a4f:	e8 cc f2 ff ff       	callq  400d20 <socket@plt>
  401a54:	41 89 c5             	mov    %eax,%r13d
  401a57:	85 c0                	test   %eax,%eax
  401a59:	79 58                	jns    401ab3 <submitr+0xbe>
  401a5b:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401a62:	41 c7 46 04 72 3a 20 	movl   $0x43203a72,0x4(%r14)
  401a69:	43 
  401a6a:	41 c7 46 08 6c 69 65 	movl   $0x6e65696c,0x8(%r14)
  401a71:	6e 
  401a72:	41 c7 46 0c 74 20 75 	movl   $0x6e752074,0xc(%r14)
  401a79:	6e 
  401a7a:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  401a81:	65 
  401a82:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  401a89:	20 
  401a8a:	41 c7 46 18 63 72 65 	movl   $0x61657263,0x18(%r14)
  401a91:	61 
  401a92:	41 c7 46 1c 74 65 20 	movl   $0x73206574,0x1c(%r14)
  401a99:	73 
  401a9a:	41 c7 46 20 6f 63 6b 	movl   $0x656b636f,0x20(%r14)
  401aa1:	65 
  401aa2:	66 41 c7 46 24 74 00 	movw   $0x74,0x24(%r14)
  401aa9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401aae:	e9 bc 07 00 00       	jmpq   40226f <submitr+0x87a>
  401ab3:	4c 89 ff             	mov    %r15,%rdi
  401ab6:	e8 75 f1 ff ff       	callq  400c30 <gethostbyname@plt>
  401abb:	48 85 c0             	test   %rax,%rax
  401abe:	0f 85 85 00 00 00    	jne    401b49 <submitr+0x154>
  401ac4:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401acb:	41 c7 46 04 72 3a 20 	movl   $0x44203a72,0x4(%r14)
  401ad2:	44 
  401ad3:	41 c7 46 08 4e 53 20 	movl   $0x6920534e,0x8(%r14)
  401ada:	69 
  401adb:	41 c7 46 0c 73 20 75 	movl   $0x6e752073,0xc(%r14)
  401ae2:	6e 
  401ae3:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  401aea:	65 
  401aeb:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  401af2:	20 
  401af3:	41 c7 46 18 72 65 73 	movl   $0x6f736572,0x18(%r14)
  401afa:	6f 
  401afb:	41 c7 46 1c 6c 76 65 	movl   $0x2065766c,0x1c(%r14)
  401b02:	20 
  401b03:	41 c7 46 20 41 75 74 	movl   $0x6f747541,0x20(%r14)
  401b0a:	6f 
  401b0b:	41 c7 46 24 6c 61 62 	movl   $0x2062616c,0x24(%r14)
  401b12:	20 
  401b13:	41 c7 46 28 73 65 72 	movl   $0x76726573,0x28(%r14)
  401b1a:	76 
  401b1b:	41 c7 46 2c 65 72 20 	movl   $0x61207265,0x2c(%r14)
  401b22:	61 
  401b23:	41 c7 46 30 64 64 72 	movl   $0x65726464,0x30(%r14)
  401b2a:	65 
  401b2b:	66 41 c7 46 34 73 73 	movw   $0x7373,0x34(%r14)
  401b32:	41 c6 46 36 00       	movb   $0x0,0x36(%r14)
  401b37:	44 89 ef             	mov    %r13d,%edi
  401b3a:	e8 a1 f0 ff ff       	callq  400be0 <close@plt>
  401b3f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401b44:	e9 26 07 00 00       	jmpq   40226f <submitr+0x87a>
  401b49:	48 c7 84 24 60 a0 00 	movq   $0x0,0xa060(%rsp)
  401b50:	00 00 00 00 00 
  401b55:	48 c7 84 24 68 a0 00 	movq   $0x0,0xa068(%rsp)
  401b5c:	00 00 00 00 00 
  401b61:	66 c7 84 24 60 a0 00 	movw   $0x2,0xa060(%rsp)
  401b68:	00 02 00 
  401b6b:	48 63 50 14          	movslq 0x14(%rax),%rdx
  401b6f:	48 8b 40 18          	mov    0x18(%rax),%rax
  401b73:	48 8d bc 24 64 a0 00 	lea    0xa064(%rsp),%rdi
  401b7a:	00 
  401b7b:	b9 0c 00 00 00       	mov    $0xc,%ecx
  401b80:	48 8b 30             	mov    (%rax),%rsi
  401b83:	e8 b8 f0 ff ff       	callq  400c40 <__memmove_chk@plt>
  401b88:	66 c1 cd 08          	ror    $0x8,%bp
  401b8c:	66 89 ac 24 62 a0 00 	mov    %bp,0xa062(%rsp)
  401b93:	00 
  401b94:	ba 10 00 00 00       	mov    $0x10,%edx
  401b99:	48 8d b4 24 60 a0 00 	lea    0xa060(%rsp),%rsi
  401ba0:	00 
  401ba1:	44 89 ef             	mov    %r13d,%edi
  401ba4:	e8 27 f1 ff ff       	callq  400cd0 <connect@plt>
  401ba9:	85 c0                	test   %eax,%eax
  401bab:	79 75                	jns    401c22 <submitr+0x22d>
  401bad:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401bb4:	41 c7 46 04 72 3a 20 	movl   $0x55203a72,0x4(%r14)
  401bbb:	55 
  401bbc:	41 c7 46 08 6e 61 62 	movl   $0x6c62616e,0x8(%r14)
  401bc3:	6c 
  401bc4:	41 c7 46 0c 65 20 74 	movl   $0x6f742065,0xc(%r14)
  401bcb:	6f 
  401bcc:	41 c7 46 10 20 63 6f 	movl   $0x6e6f6320,0x10(%r14)
  401bd3:	6e 
  401bd4:	41 c7 46 14 6e 65 63 	movl   $0x7463656e,0x14(%r14)
  401bdb:	74 
  401bdc:	41 c7 46 18 20 74 6f 	movl   $0x206f7420,0x18(%r14)
  401be3:	20 
  401be4:	41 c7 46 1c 74 68 65 	movl   $0x20656874,0x1c(%r14)
  401beb:	20 
  401bec:	41 c7 46 20 41 75 74 	movl   $0x6f747541,0x20(%r14)
  401bf3:	6f 
  401bf4:	41 c7 46 24 6c 61 62 	movl   $0x2062616c,0x24(%r14)
  401bfb:	20 
  401bfc:	41 c7 46 28 73 65 72 	movl   $0x76726573,0x28(%r14)
  401c03:	76 
  401c04:	66 41 c7 46 2c 65 72 	movw   $0x7265,0x2c(%r14)
  401c0b:	41 c6 46 2e 00       	movb   $0x0,0x2e(%r14)
  401c10:	44 89 ef             	mov    %r13d,%edi
  401c13:	e8 c8 ef ff ff       	callq  400be0 <close@plt>
  401c18:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401c1d:	e9 4d 06 00 00       	jmpq   40226f <submitr+0x87a>
  401c22:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  401c29:	48 89 df             	mov    %rbx,%rdi
  401c2c:	b8 00 00 00 00       	mov    $0x0,%eax
  401c31:	48 89 d1             	mov    %rdx,%rcx
  401c34:	f2 ae                	repnz scas %es:(%rdi),%al
  401c36:	48 89 ce             	mov    %rcx,%rsi
  401c39:	48 f7 d6             	not    %rsi
  401c3c:	48 8b 7c 24 28       	mov    0x28(%rsp),%rdi
  401c41:	48 89 d1             	mov    %rdx,%rcx
  401c44:	f2 ae                	repnz scas %es:(%rdi),%al
  401c46:	49 89 c8             	mov    %rcx,%r8
  401c49:	48 8b 7c 24 30       	mov    0x30(%rsp),%rdi
  401c4e:	48 89 d1             	mov    %rdx,%rcx
  401c51:	f2 ae                	repnz scas %es:(%rdi),%al
  401c53:	49 89 c9             	mov    %rcx,%r9
  401c56:	49 f7 d1             	not    %r9
  401c59:	48 8b 7c 24 38       	mov    0x38(%rsp),%rdi
  401c5e:	48 89 d1             	mov    %rdx,%rcx
  401c61:	f2 ae                	repnz scas %es:(%rdi),%al
  401c63:	4d 29 c1             	sub    %r8,%r9
  401c66:	49 29 c9             	sub    %rcx,%r9
  401c69:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
  401c6e:	49 8d 44 01 7b       	lea    0x7b(%r9,%rax,1),%rax
  401c73:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  401c79:	0f 86 81 00 00 00    	jbe    401d00 <submitr+0x30b>
  401c7f:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401c86:	41 c7 46 04 72 3a 20 	movl   $0x52203a72,0x4(%r14)
  401c8d:	52 
  401c8e:	41 c7 46 08 65 73 75 	movl   $0x6c757365,0x8(%r14)
  401c95:	6c 
  401c96:	41 c7 46 0c 74 20 73 	movl   $0x74732074,0xc(%r14)
  401c9d:	74 
  401c9e:	41 c7 46 10 72 69 6e 	movl   $0x676e6972,0x10(%r14)
  401ca5:	67 
  401ca6:	41 c7 46 14 20 74 6f 	movl   $0x6f6f7420,0x14(%r14)
  401cad:	6f 
  401cae:	41 c7 46 18 20 6c 61 	movl   $0x72616c20,0x18(%r14)
  401cb5:	72 
  401cb6:	41 c7 46 1c 67 65 2e 	movl   $0x202e6567,0x1c(%r14)
  401cbd:	20 
  401cbe:	41 c7 46 20 49 6e 63 	movl   $0x72636e49,0x20(%r14)
  401cc5:	72 
  401cc6:	41 c7 46 24 65 61 73 	movl   $0x65736165,0x24(%r14)
  401ccd:	65 
  401cce:	41 c7 46 28 20 53 55 	movl   $0x42555320,0x28(%r14)
  401cd5:	42 
  401cd6:	41 c7 46 2c 4d 49 54 	movl   $0x5254494d,0x2c(%r14)
  401cdd:	52 
  401cde:	41 c7 46 30 5f 4d 41 	movl   $0x58414d5f,0x30(%r14)
  401ce5:	58 
  401ce6:	41 c7 46 34 42 55 46 	movl   $0x465542,0x34(%r14)
  401ced:	00 
  401cee:	44 89 ef             	mov    %r13d,%edi
  401cf1:	e8 ea ee ff ff       	callq  400be0 <close@plt>
  401cf6:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401cfb:	e9 6f 05 00 00       	jmpq   40226f <submitr+0x87a>
  401d00:	48 8d 94 24 60 40 00 	lea    0x4060(%rsp),%rdx
  401d07:	00 
  401d08:	b9 00 04 00 00       	mov    $0x400,%ecx
  401d0d:	b8 00 00 00 00       	mov    $0x0,%eax
  401d12:	48 89 d7             	mov    %rdx,%rdi
  401d15:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  401d18:	48 89 df             	mov    %rbx,%rdi
  401d1b:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401d22:	f2 ae                	repnz scas %es:(%rdi),%al
  401d24:	48 f7 d1             	not    %rcx
  401d27:	48 83 e9 01          	sub    $0x1,%rcx
  401d2b:	85 c9                	test   %ecx,%ecx
  401d2d:	0f 84 55 05 00 00    	je     402288 <submitr+0x893>
  401d33:	83 e9 01             	sub    $0x1,%ecx
  401d36:	4c 8d 64 0b 01       	lea    0x1(%rbx,%rcx,1),%r12
  401d3b:	48 89 d5             	mov    %rdx,%rbp
  401d3e:	44 0f b6 03          	movzbl (%rbx),%r8d
  401d42:	41 80 f8 2a          	cmp    $0x2a,%r8b
  401d46:	74 2a                	je     401d72 <submitr+0x37d>
  401d48:	41 80 f8 2d          	cmp    $0x2d,%r8b
  401d4c:	74 24                	je     401d72 <submitr+0x37d>
  401d4e:	41 80 f8 2e          	cmp    $0x2e,%r8b
  401d52:	74 1e                	je     401d72 <submitr+0x37d>
  401d54:	41 80 f8 5f          	cmp    $0x5f,%r8b
  401d58:	74 18                	je     401d72 <submitr+0x37d>
  401d5a:	41 8d 40 d0          	lea    -0x30(%r8),%eax
  401d5e:	3c 09                	cmp    $0x9,%al
  401d60:	76 10                	jbe    401d72 <submitr+0x37d>
  401d62:	41 8d 40 bf          	lea    -0x41(%r8),%eax
  401d66:	3c 19                	cmp    $0x19,%al
  401d68:	76 08                	jbe    401d72 <submitr+0x37d>
  401d6a:	41 8d 40 9f          	lea    -0x61(%r8),%eax
  401d6e:	3c 19                	cmp    $0x19,%al
  401d70:	77 0a                	ja     401d7c <submitr+0x387>
  401d72:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  401d76:	48 83 c5 01          	add    $0x1,%rbp
  401d7a:	eb 68                	jmp    401de4 <submitr+0x3ef>
  401d7c:	41 80 f8 20          	cmp    $0x20,%r8b
  401d80:	75 0a                	jne    401d8c <submitr+0x397>
  401d82:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  401d86:	48 83 c5 01          	add    $0x1,%rbp
  401d8a:	eb 58                	jmp    401de4 <submitr+0x3ef>
  401d8c:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  401d90:	3c 5f                	cmp    $0x5f,%al
  401d92:	76 06                	jbe    401d9a <submitr+0x3a5>
  401d94:	41 80 f8 09          	cmp    $0x9,%r8b
  401d98:	75 5c                	jne    401df6 <submitr+0x401>
  401d9a:	45 0f b6 c0          	movzbl %r8b,%r8d
  401d9e:	b9 a0 2d 40 00       	mov    $0x402da0,%ecx
  401da3:	ba 08 00 00 00       	mov    $0x8,%edx
  401da8:	be 01 00 00 00       	mov    $0x1,%esi
  401dad:	48 8d bc 24 70 a0 00 	lea    0xa070(%rsp),%rdi
  401db4:	00 
  401db5:	b8 00 00 00 00       	mov    $0x0,%eax
  401dba:	e8 51 ef ff ff       	callq  400d10 <__sprintf_chk@plt>
  401dbf:	0f b6 84 24 70 a0 00 	movzbl 0xa070(%rsp),%eax
  401dc6:	00 
  401dc7:	88 45 00             	mov    %al,0x0(%rbp)
  401dca:	0f b6 84 24 71 a0 00 	movzbl 0xa071(%rsp),%eax
  401dd1:	00 
  401dd2:	88 45 01             	mov    %al,0x1(%rbp)
  401dd5:	0f b6 84 24 72 a0 00 	movzbl 0xa072(%rsp),%eax
  401ddc:	00 
  401ddd:	88 45 02             	mov    %al,0x2(%rbp)
  401de0:	48 83 c5 03          	add    $0x3,%rbp
  401de4:	48 83 c3 01          	add    $0x1,%rbx
  401de8:	4c 39 e3             	cmp    %r12,%rbx
  401deb:	0f 85 4d ff ff ff    	jne    401d3e <submitr+0x349>
  401df1:	e9 92 04 00 00       	jmpq   402288 <submitr+0x893>
  401df6:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401dfd:	41 c7 46 04 72 3a 20 	movl   $0x52203a72,0x4(%r14)
  401e04:	52 
  401e05:	41 c7 46 08 65 73 75 	movl   $0x6c757365,0x8(%r14)
  401e0c:	6c 
  401e0d:	41 c7 46 0c 74 20 73 	movl   $0x74732074,0xc(%r14)
  401e14:	74 
  401e15:	41 c7 46 10 72 69 6e 	movl   $0x676e6972,0x10(%r14)
  401e1c:	67 
  401e1d:	41 c7 46 14 20 63 6f 	movl   $0x6e6f6320,0x14(%r14)
  401e24:	6e 
  401e25:	41 c7 46 18 74 61 69 	movl   $0x6e696174,0x18(%r14)
  401e2c:	6e 
  401e2d:	41 c7 46 1c 73 20 61 	movl   $0x6e612073,0x1c(%r14)
  401e34:	6e 
  401e35:	41 c7 46 20 20 69 6c 	movl   $0x6c6c6920,0x20(%r14)
  401e3c:	6c 
  401e3d:	41 c7 46 24 65 67 61 	movl   $0x6c616765,0x24(%r14)
  401e44:	6c 
  401e45:	41 c7 46 28 20 6f 72 	movl   $0x20726f20,0x28(%r14)
  401e4c:	20 
  401e4d:	41 c7 46 2c 75 6e 70 	movl   $0x72706e75,0x2c(%r14)
  401e54:	72 
  401e55:	41 c7 46 30 69 6e 74 	movl   $0x61746e69,0x30(%r14)
  401e5c:	61 
  401e5d:	41 c7 46 34 62 6c 65 	movl   $0x20656c62,0x34(%r14)
  401e64:	20 
  401e65:	41 c7 46 38 63 68 61 	movl   $0x72616863,0x38(%r14)
  401e6c:	72 
  401e6d:	41 c7 46 3c 61 63 74 	movl   $0x65746361,0x3c(%r14)
  401e74:	65 
  401e75:	66 41 c7 46 40 72 2e 	movw   $0x2e72,0x40(%r14)
  401e7c:	41 c6 46 42 00       	movb   $0x0,0x42(%r14)
  401e81:	44 89 ef             	mov    %r13d,%edi
  401e84:	e8 57 ed ff ff       	callq  400be0 <close@plt>
  401e89:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401e8e:	e9 dc 03 00 00       	jmpq   40226f <submitr+0x87a>
  401e93:	48 89 da             	mov    %rbx,%rdx
  401e96:	48 89 ee             	mov    %rbp,%rsi
  401e99:	44 89 ef             	mov    %r13d,%edi
  401e9c:	e8 0f ed ff ff       	callq  400bb0 <write@plt>
  401ea1:	48 85 c0             	test   %rax,%rax
  401ea4:	7f 11                	jg     401eb7 <submitr+0x4c2>
  401ea6:	e8 d5 ec ff ff       	callq  400b80 <__errno_location@plt>
  401eab:	83 38 04             	cmpl   $0x4,(%rax)
  401eae:	66 90                	xchg   %ax,%ax
  401eb0:	75 12                	jne    401ec4 <submitr+0x4cf>
  401eb2:	b8 00 00 00 00       	mov    $0x0,%eax
  401eb7:	48 01 c5             	add    %rax,%rbp
  401eba:	48 29 c3             	sub    %rax,%rbx
  401ebd:	75 d4                	jne    401e93 <submitr+0x49e>
  401ebf:	4d 85 e4             	test   %r12,%r12
  401ec2:	79 79                	jns    401f3d <submitr+0x548>
  401ec4:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401ecb:	41 c7 46 04 72 3a 20 	movl   $0x43203a72,0x4(%r14)
  401ed2:	43 
  401ed3:	41 c7 46 08 6c 69 65 	movl   $0x6e65696c,0x8(%r14)
  401eda:	6e 
  401edb:	41 c7 46 0c 74 20 75 	movl   $0x6e752074,0xc(%r14)
  401ee2:	6e 
  401ee3:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  401eea:	65 
  401eeb:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  401ef2:	20 
  401ef3:	41 c7 46 18 77 72 69 	movl   $0x74697277,0x18(%r14)
  401efa:	74 
  401efb:	41 c7 46 1c 65 20 74 	movl   $0x6f742065,0x1c(%r14)
  401f02:	6f 
  401f03:	41 c7 46 20 20 74 68 	movl   $0x65687420,0x20(%r14)
  401f0a:	65 
  401f0b:	41 c7 46 24 20 41 75 	movl   $0x74754120,0x24(%r14)
  401f12:	74 
  401f13:	41 c7 46 28 6f 6c 61 	movl   $0x62616c6f,0x28(%r14)
  401f1a:	62 
  401f1b:	41 c7 46 2c 20 73 65 	movl   $0x72657320,0x2c(%r14)
  401f22:	72 
  401f23:	41 c7 46 30 76 65 72 	movl   $0x726576,0x30(%r14)
  401f2a:	00 
  401f2b:	44 89 ef             	mov    %r13d,%edi
  401f2e:	e8 ad ec ff ff       	callq  400be0 <close@plt>
  401f33:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401f38:	e9 32 03 00 00       	jmpq   40226f <submitr+0x87a>
  401f3d:	44 89 6c 24 50       	mov    %r13d,0x50(%rsp)
  401f42:	c7 44 24 54 00 00 00 	movl   $0x0,0x54(%rsp)
  401f49:	00 
  401f4a:	48 8d 44 24 60       	lea    0x60(%rsp),%rax
  401f4f:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  401f54:	ba 00 20 00 00       	mov    $0x2000,%edx
  401f59:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
  401f60:	00 
  401f61:	48 8d 7c 24 50       	lea    0x50(%rsp),%rdi
  401f66:	e8 45 f9 ff ff       	callq  4018b0 <rio_readlineb>
  401f6b:	48 85 c0             	test   %rax,%rax
  401f6e:	0f 8f 90 00 00 00    	jg     402004 <submitr+0x60f>
  401f74:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  401f7b:	41 c7 46 04 72 3a 20 	movl   $0x43203a72,0x4(%r14)
  401f82:	43 
  401f83:	41 c7 46 08 6c 69 65 	movl   $0x6e65696c,0x8(%r14)
  401f8a:	6e 
  401f8b:	41 c7 46 0c 74 20 75 	movl   $0x6e752074,0xc(%r14)
  401f92:	6e 
  401f93:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  401f9a:	65 
  401f9b:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  401fa2:	20 
  401fa3:	41 c7 46 18 72 65 61 	movl   $0x64616572,0x18(%r14)
  401faa:	64 
  401fab:	41 c7 46 1c 20 66 69 	movl   $0x72696620,0x1c(%r14)
  401fb2:	72 
  401fb3:	41 c7 46 20 73 74 20 	movl   $0x68207473,0x20(%r14)
  401fba:	68 
  401fbb:	41 c7 46 24 65 61 64 	movl   $0x65646165,0x24(%r14)
  401fc2:	65 
  401fc3:	41 c7 46 28 72 20 66 	movl   $0x72662072,0x28(%r14)
  401fca:	72 
  401fcb:	41 c7 46 2c 6f 6d 20 	movl   $0x41206d6f,0x2c(%r14)
  401fd2:	41 
  401fd3:	41 c7 46 30 75 74 6f 	movl   $0x6c6f7475,0x30(%r14)
  401fda:	6c 
  401fdb:	41 c7 46 34 61 62 20 	movl   $0x73206261,0x34(%r14)
  401fe2:	73 
  401fe3:	41 c7 46 38 65 72 76 	movl   $0x65767265,0x38(%r14)
  401fea:	65 
  401feb:	66 41 c7 46 3c 72 00 	movw   $0x72,0x3c(%r14)
  401ff2:	44 89 ef             	mov    %r13d,%edi
  401ff5:	e8 e6 eb ff ff       	callq  400be0 <close@plt>
  401ffa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401fff:	e9 6b 02 00 00       	jmpq   40226f <submitr+0x87a>
  402004:	4c 8d 84 24 60 80 00 	lea    0x8060(%rsp),%r8
  40200b:	00 
  40200c:	48 8d 4c 24 4c       	lea    0x4c(%rsp),%rcx
  402011:	48 8d 94 24 60 60 00 	lea    0x6060(%rsp),%rdx
  402018:	00 
  402019:	be a7 2d 40 00       	mov    $0x402da7,%esi
  40201e:	48 8d bc 24 60 20 00 	lea    0x2060(%rsp),%rdi
  402025:	00 
  402026:	b8 00 00 00 00       	mov    $0x0,%eax
  40202b:	e8 50 ec ff ff       	callq  400c80 <__isoc99_sscanf@plt>
  402030:	e9 a6 00 00 00       	jmpq   4020db <submitr+0x6e6>
  402035:	ba 00 20 00 00       	mov    $0x2000,%edx
  40203a:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
  402041:	00 
  402042:	48 8d 7c 24 50       	lea    0x50(%rsp),%rdi
  402047:	e8 64 f8 ff ff       	callq  4018b0 <rio_readlineb>
  40204c:	48 85 c0             	test   %rax,%rax
  40204f:	0f 8f 86 00 00 00    	jg     4020db <submitr+0x6e6>
  402055:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  40205c:	41 c7 46 04 72 3a 20 	movl   $0x43203a72,0x4(%r14)
  402063:	43 
  402064:	41 c7 46 08 6c 69 65 	movl   $0x6e65696c,0x8(%r14)
  40206b:	6e 
  40206c:	41 c7 46 0c 74 20 75 	movl   $0x6e752074,0xc(%r14)
  402073:	6e 
  402074:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  40207b:	65 
  40207c:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  402083:	20 
  402084:	41 c7 46 18 72 65 61 	movl   $0x64616572,0x18(%r14)
  40208b:	64 
  40208c:	41 c7 46 1c 20 68 65 	movl   $0x61656820,0x1c(%r14)
  402093:	61 
  402094:	41 c7 46 20 64 65 72 	movl   $0x73726564,0x20(%r14)
  40209b:	73 
  40209c:	41 c7 46 24 20 66 72 	movl   $0x6f726620,0x24(%r14)
  4020a3:	6f 
  4020a4:	41 c7 46 28 6d 20 41 	movl   $0x7541206d,0x28(%r14)
  4020ab:	75 
  4020ac:	41 c7 46 2c 74 6f 6c 	movl   $0x616c6f74,0x2c(%r14)
  4020b3:	61 
  4020b4:	41 c7 46 30 62 20 73 	movl   $0x65732062,0x30(%r14)
  4020bb:	65 
  4020bc:	41 c7 46 34 72 76 65 	movl   $0x72657672,0x34(%r14)
  4020c3:	72 
  4020c4:	41 c6 46 38 00       	movb   $0x0,0x38(%r14)
  4020c9:	44 89 ef             	mov    %r13d,%edi
  4020cc:	e8 0f eb ff ff       	callq  400be0 <close@plt>
  4020d1:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4020d6:	e9 94 01 00 00       	jmpq   40226f <submitr+0x87a>
  4020db:	80 bc 24 60 20 00 00 	cmpb   $0xd,0x2060(%rsp)
  4020e2:	0d 
  4020e3:	0f 85 4c ff ff ff    	jne    402035 <submitr+0x640>
  4020e9:	80 bc 24 61 20 00 00 	cmpb   $0xa,0x2061(%rsp)
  4020f0:	0a 
  4020f1:	0f 85 3e ff ff ff    	jne    402035 <submitr+0x640>
  4020f7:	80 bc 24 62 20 00 00 	cmpb   $0x0,0x2062(%rsp)
  4020fe:	00 
  4020ff:	0f 85 30 ff ff ff    	jne    402035 <submitr+0x640>
  402105:	ba 00 20 00 00       	mov    $0x2000,%edx
  40210a:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
  402111:	00 
  402112:	48 8d 7c 24 50       	lea    0x50(%rsp),%rdi
  402117:	e8 94 f7 ff ff       	callq  4018b0 <rio_readlineb>
  40211c:	48 85 c0             	test   %rax,%rax
  40211f:	0f 8f 91 00 00 00    	jg     4021b6 <submitr+0x7c1>
  402125:	41 c7 06 45 72 72 6f 	movl   $0x6f727245,(%r14)
  40212c:	41 c7 46 04 72 3a 20 	movl   $0x43203a72,0x4(%r14)
  402133:	43 
  402134:	41 c7 46 08 6c 69 65 	movl   $0x6e65696c,0x8(%r14)
  40213b:	6e 
  40213c:	41 c7 46 0c 74 20 75 	movl   $0x6e752074,0xc(%r14)
  402143:	6e 
  402144:	41 c7 46 10 61 62 6c 	movl   $0x656c6261,0x10(%r14)
  40214b:	65 
  40214c:	41 c7 46 14 20 74 6f 	movl   $0x206f7420,0x14(%r14)
  402153:	20 
  402154:	41 c7 46 18 72 65 61 	movl   $0x64616572,0x18(%r14)
  40215b:	64 
  40215c:	41 c7 46 1c 20 73 74 	movl   $0x61747320,0x1c(%r14)
  402163:	61 
  402164:	41 c7 46 20 74 75 73 	movl   $0x20737574,0x20(%r14)
  40216b:	20 
  40216c:	41 c7 46 24 6d 65 73 	movl   $0x7373656d,0x24(%r14)
  402173:	73 
  402174:	41 c7 46 28 61 67 65 	movl   $0x20656761,0x28(%r14)
  40217b:	20 
  40217c:	41 c7 46 2c 66 72 6f 	movl   $0x6d6f7266,0x2c(%r14)
  402183:	6d 
  402184:	41 c7 46 30 20 41 75 	movl   $0x74754120,0x30(%r14)
  40218b:	74 
  40218c:	41 c7 46 34 6f 6c 61 	movl   $0x62616c6f,0x34(%r14)
  402193:	62 
  402194:	41 c7 46 38 20 73 65 	movl   $0x72657320,0x38(%r14)
  40219b:	72 
  40219c:	41 c7 46 3c 76 65 72 	movl   $0x726576,0x3c(%r14)
  4021a3:	00 
  4021a4:	44 89 ef             	mov    %r13d,%edi
  4021a7:	e8 34 ea ff ff       	callq  400be0 <close@plt>
  4021ac:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4021b1:	e9 b9 00 00 00       	jmpq   40226f <submitr+0x87a>
  4021b6:	44 8b 44 24 4c       	mov    0x4c(%rsp),%r8d
  4021bb:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  4021c2:	74 35                	je     4021f9 <submitr+0x804>
  4021c4:	4c 8d 8c 24 60 80 00 	lea    0x8060(%rsp),%r9
  4021cb:	00 
  4021cc:	b9 10 2d 40 00       	mov    $0x402d10,%ecx
  4021d1:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  4021d8:	be 01 00 00 00       	mov    $0x1,%esi
  4021dd:	4c 89 f7             	mov    %r14,%rdi
  4021e0:	b8 00 00 00 00       	mov    $0x0,%eax
  4021e5:	e8 26 eb ff ff       	callq  400d10 <__sprintf_chk@plt>
  4021ea:	44 89 ef             	mov    %r13d,%edi
  4021ed:	e8 ee e9 ff ff       	callq  400be0 <close@plt>
  4021f2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4021f7:	eb 76                	jmp    40226f <submitr+0x87a>
  4021f9:	48 8d b4 24 60 20 00 	lea    0x2060(%rsp),%rsi
  402200:	00 
  402201:	4c 89 f7             	mov    %r14,%rdi
  402204:	e8 87 e9 ff ff       	callq  400b90 <strcpy@plt>
  402209:	44 89 ef             	mov    %r13d,%edi
  40220c:	e8 cf e9 ff ff       	callq  400be0 <close@plt>
  402211:	41 0f b6 16          	movzbl (%r14),%edx
  402215:	83 ea 4f             	sub    $0x4f,%edx
  402218:	75 15                	jne    40222f <submitr+0x83a>
  40221a:	41 80 7e 01 4b       	cmpb   $0x4b,0x1(%r14)
  40221f:	75 0e                	jne    40222f <submitr+0x83a>
  402221:	41 80 7e 02 0a       	cmpb   $0xa,0x2(%r14)
  402226:	75 07                	jne    40222f <submitr+0x83a>
  402228:	41 80 7e 03 00       	cmpb   $0x0,0x3(%r14)
  40222d:	74 3b                	je     40226a <submitr+0x875>
  40222f:	bf b8 2d 40 00       	mov    $0x402db8,%edi
  402234:	b9 05 00 00 00       	mov    $0x5,%ecx
  402239:	4c 89 f6             	mov    %r14,%rsi
  40223c:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  40223e:	40 0f 97 c6          	seta   %sil
  402242:	0f 92 c1             	setb   %cl
  402245:	b8 00 00 00 00       	mov    $0x0,%eax
  40224a:	40 38 ce             	cmp    %cl,%sil
  40224d:	74 20                	je     40226f <submitr+0x87a>
  40224f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402254:	85 d2                	test   %edx,%edx
  402256:	75 17                	jne    40226f <submitr+0x87a>
  402258:	41 80 7e 01 4b       	cmpb   $0x4b,0x1(%r14)
  40225d:	75 10                	jne    40226f <submitr+0x87a>
  40225f:	41 80 7e 02 01       	cmpb   $0x1,0x2(%r14)
  402264:	19 c0                	sbb    %eax,%eax
  402266:	f7 d0                	not    %eax
  402268:	eb 05                	jmp    40226f <submitr+0x87a>
  40226a:	b8 00 00 00 00       	mov    $0x0,%eax
  40226f:	48 8b 94 24 78 a0 00 	mov    0xa078(%rsp),%rdx
  402276:	00 
  402277:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  40227e:	00 00 
  402280:	0f 84 83 00 00 00    	je     402309 <submitr+0x914>
  402286:	eb 7c                	jmp    402304 <submitr+0x90f>
  402288:	4c 89 7c 24 10       	mov    %r15,0x10(%rsp)
  40228d:	48 8d 84 24 60 40 00 	lea    0x4060(%rsp),%rax
  402294:	00 
  402295:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  40229a:	48 8b 4c 24 30       	mov    0x30(%rsp),%rcx
  40229f:	48 89 0c 24          	mov    %rcx,(%rsp)
  4022a3:	4c 8b 4c 24 38       	mov    0x38(%rsp),%r9
  4022a8:	4c 8b 44 24 28       	mov    0x28(%rsp),%r8
  4022ad:	b9 40 2d 40 00       	mov    $0x402d40,%ecx
  4022b2:	ba 00 20 00 00       	mov    $0x2000,%edx
  4022b7:	be 01 00 00 00       	mov    $0x1,%esi
  4022bc:	48 8d bc 24 60 20 00 	lea    0x2060(%rsp),%rdi
  4022c3:	00 
  4022c4:	b8 00 00 00 00       	mov    $0x0,%eax
  4022c9:	e8 42 ea ff ff       	callq  400d10 <__sprintf_chk@plt>
  4022ce:	48 8d bc 24 60 20 00 	lea    0x2060(%rsp),%rdi
  4022d5:	00 
  4022d6:	b8 00 00 00 00       	mov    $0x0,%eax
  4022db:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4022e2:	f2 ae                	repnz scas %es:(%rdi),%al
  4022e4:	48 f7 d1             	not    %rcx
  4022e7:	4c 8d 61 ff          	lea    -0x1(%rcx),%r12
  4022eb:	4c 89 e3             	mov    %r12,%rbx
  4022ee:	48 8d ac 24 60 20 00 	lea    0x2060(%rsp),%rbp
  4022f5:	00 
  4022f6:	4d 85 e4             	test   %r12,%r12
  4022f9:	0f 85 94 fb ff ff    	jne    401e93 <submitr+0x49e>
  4022ff:	e9 39 fc ff ff       	jmpq   401f3d <submitr+0x548>
  402304:	e8 b7 e8 ff ff       	callq  400bc0 <__stack_chk_fail@plt>
  402309:	48 81 c4 88 a0 00 00 	add    $0xa088,%rsp
  402310:	5b                   	pop    %rbx
  402311:	5d                   	pop    %rbp
  402312:	41 5c                	pop    %r12
  402314:	41 5d                	pop    %r13
  402316:	41 5e                	pop    %r14
  402318:	41 5f                	pop    %r15
  40231a:	c3                   	retq   

000000000040231b <init_timeout>:
  40231b:	53                   	push   %rbx
  40231c:	89 fb                	mov    %edi,%ebx
  40231e:	85 ff                	test   %edi,%edi
  402320:	74 1e                	je     402340 <init_timeout+0x25>
  402322:	be c7 19 40 00       	mov    $0x4019c7,%esi
  402327:	bf 0e 00 00 00       	mov    $0xe,%edi
  40232c:	e8 ef e8 ff ff       	callq  400c20 <signal@plt>
  402331:	85 db                	test   %ebx,%ebx
  402333:	bf 00 00 00 00       	mov    $0x0,%edi
  402338:	0f 49 fb             	cmovns %ebx,%edi
  40233b:	e8 90 e8 ff ff       	callq  400bd0 <alarm@plt>
  402340:	5b                   	pop    %rbx
  402341:	c3                   	retq   

0000000000402342 <init_driver>:
  402342:	55                   	push   %rbp
  402343:	53                   	push   %rbx
  402344:	48 83 ec 28          	sub    $0x28,%rsp
  402348:	48 89 fd             	mov    %rdi,%rbp
  40234b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402352:	00 00 
  402354:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402359:	31 c0                	xor    %eax,%eax
  40235b:	be 01 00 00 00       	mov    $0x1,%esi
  402360:	bf 0d 00 00 00       	mov    $0xd,%edi
  402365:	e8 b6 e8 ff ff       	callq  400c20 <signal@plt>
  40236a:	be 01 00 00 00       	mov    $0x1,%esi
  40236f:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402374:	e8 a7 e8 ff ff       	callq  400c20 <signal@plt>
  402379:	be 01 00 00 00       	mov    $0x1,%esi
  40237e:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402383:	e8 98 e8 ff ff       	callq  400c20 <signal@plt>
  402388:	ba 00 00 00 00       	mov    $0x0,%edx
  40238d:	be 01 00 00 00       	mov    $0x1,%esi
  402392:	bf 02 00 00 00       	mov    $0x2,%edi
  402397:	e8 84 e9 ff ff       	callq  400d20 <socket@plt>
  40239c:	89 c3                	mov    %eax,%ebx
  40239e:	85 c0                	test   %eax,%eax
  4023a0:	79 4f                	jns    4023f1 <init_driver+0xaf>
  4023a2:	c7 45 00 45 72 72 6f 	movl   $0x6f727245,0x0(%rbp)
  4023a9:	c7 45 04 72 3a 20 43 	movl   $0x43203a72,0x4(%rbp)
  4023b0:	c7 45 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%rbp)
  4023b7:	c7 45 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%rbp)
  4023be:	c7 45 10 61 62 6c 65 	movl   $0x656c6261,0x10(%rbp)
  4023c5:	c7 45 14 20 74 6f 20 	movl   $0x206f7420,0x14(%rbp)
  4023cc:	c7 45 18 63 72 65 61 	movl   $0x61657263,0x18(%rbp)
  4023d3:	c7 45 1c 74 65 20 73 	movl   $0x73206574,0x1c(%rbp)
  4023da:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  4023e1:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  4023e7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4023ec:	e9 28 01 00 00       	jmpq   402519 <init_driver+0x1d7>
  4023f1:	bf cb 2b 40 00       	mov    $0x402bcb,%edi
  4023f6:	e8 35 e8 ff ff       	callq  400c30 <gethostbyname@plt>
  4023fb:	48 85 c0             	test   %rax,%rax
  4023fe:	75 68                	jne    402468 <init_driver+0x126>
  402400:	c7 45 00 45 72 72 6f 	movl   $0x6f727245,0x0(%rbp)
  402407:	c7 45 04 72 3a 20 44 	movl   $0x44203a72,0x4(%rbp)
  40240e:	c7 45 08 4e 53 20 69 	movl   $0x6920534e,0x8(%rbp)
  402415:	c7 45 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%rbp)
  40241c:	c7 45 10 61 62 6c 65 	movl   $0x656c6261,0x10(%rbp)
  402423:	c7 45 14 20 74 6f 20 	movl   $0x206f7420,0x14(%rbp)
  40242a:	c7 45 18 72 65 73 6f 	movl   $0x6f736572,0x18(%rbp)
  402431:	c7 45 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%rbp)
  402438:	c7 45 20 73 65 72 76 	movl   $0x76726573,0x20(%rbp)
  40243f:	c7 45 24 65 72 20 61 	movl   $0x61207265,0x24(%rbp)
  402446:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  40244d:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402453:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402457:	89 df                	mov    %ebx,%edi
  402459:	e8 82 e7 ff ff       	callq  400be0 <close@plt>
  40245e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402463:	e9 b1 00 00 00       	jmpq   402519 <init_driver+0x1d7>
  402468:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  40246f:	00 
  402470:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402477:	00 00 
  402479:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  40247f:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402483:	48 8b 40 18          	mov    0x18(%rax),%rax
  402487:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  40248c:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402491:	48 8b 30             	mov    (%rax),%rsi
  402494:	e8 a7 e7 ff ff       	callq  400c40 <__memmove_chk@plt>
  402499:	66 c7 44 24 02 00 50 	movw   $0x5000,0x2(%rsp)
  4024a0:	ba 10 00 00 00       	mov    $0x10,%edx
  4024a5:	48 89 e6             	mov    %rsp,%rsi
  4024a8:	89 df                	mov    %ebx,%edi
  4024aa:	e8 21 e8 ff ff       	callq  400cd0 <connect@plt>
  4024af:	85 c0                	test   %eax,%eax
  4024b1:	79 50                	jns    402503 <init_driver+0x1c1>
  4024b3:	c7 45 00 45 72 72 6f 	movl   $0x6f727245,0x0(%rbp)
  4024ba:	c7 45 04 72 3a 20 55 	movl   $0x55203a72,0x4(%rbp)
  4024c1:	c7 45 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%rbp)
  4024c8:	c7 45 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%rbp)
  4024cf:	c7 45 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%rbp)
  4024d6:	c7 45 14 6e 65 63 74 	movl   $0x7463656e,0x14(%rbp)
  4024dd:	c7 45 18 20 74 6f 20 	movl   $0x206f7420,0x18(%rbp)
  4024e4:	c7 45 1c 73 65 72 76 	movl   $0x76726573,0x1c(%rbp)
  4024eb:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  4024f1:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  4024f5:	89 df                	mov    %ebx,%edi
  4024f7:	e8 e4 e6 ff ff       	callq  400be0 <close@plt>
  4024fc:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402501:	eb 16                	jmp    402519 <init_driver+0x1d7>
  402503:	89 df                	mov    %ebx,%edi
  402505:	e8 d6 e6 ff ff       	callq  400be0 <close@plt>
  40250a:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  402510:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402514:	b8 00 00 00 00       	mov    $0x0,%eax
  402519:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  40251e:	64 48 33 14 25 28 00 	xor    %fs:0x28,%rdx
  402525:	00 00 
  402527:	74 05                	je     40252e <init_driver+0x1ec>
  402529:	e8 92 e6 ff ff       	callq  400bc0 <__stack_chk_fail@plt>
  40252e:	48 83 c4 28          	add    $0x28,%rsp
  402532:	5b                   	pop    %rbx
  402533:	5d                   	pop    %rbp
  402534:	c3                   	retq   

0000000000402535 <driver_post>:
  402535:	53                   	push   %rbx
  402536:	48 83 ec 10          	sub    $0x10,%rsp
  40253a:	4c 89 cb             	mov    %r9,%rbx
  40253d:	45 85 c0             	test   %r8d,%r8d
  402540:	74 27                	je     402569 <driver_post+0x34>
  402542:	48 89 ca             	mov    %rcx,%rdx
  402545:	be bd 2d 40 00       	mov    $0x402dbd,%esi
  40254a:	bf 01 00 00 00       	mov    $0x1,%edi
  40254f:	b8 00 00 00 00       	mov    $0x0,%eax
  402554:	e8 37 e7 ff ff       	callq  400c90 <__printf_chk@plt>
  402559:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  40255e:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402562:	b8 00 00 00 00       	mov    $0x0,%eax
  402567:	eb 39                	jmp    4025a2 <driver_post+0x6d>
  402569:	48 85 ff             	test   %rdi,%rdi
  40256c:	74 26                	je     402594 <driver_post+0x5f>
  40256e:	80 3f 00             	cmpb   $0x0,(%rdi)
  402571:	74 21                	je     402594 <driver_post+0x5f>
  402573:	4c 89 0c 24          	mov    %r9,(%rsp)
  402577:	49 89 c9             	mov    %rcx,%r9
  40257a:	49 89 d0             	mov    %rdx,%r8
  40257d:	48 89 f9             	mov    %rdi,%rcx
  402580:	48 89 f2             	mov    %rsi,%rdx
  402583:	be 50 00 00 00       	mov    $0x50,%esi
  402588:	bf cb 2b 40 00       	mov    $0x402bcb,%edi
  40258d:	e8 63 f4 ff ff       	callq  4019f5 <submitr>
  402592:	eb 0e                	jmp    4025a2 <driver_post+0x6d>
  402594:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402599:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  40259d:	b8 00 00 00 00       	mov    $0x0,%eax
  4025a2:	48 83 c4 10          	add    $0x10,%rsp
  4025a6:	5b                   	pop    %rbx
  4025a7:	c3                   	retq   
  4025a8:	90                   	nop
  4025a9:	90                   	nop
  4025aa:	90                   	nop
  4025ab:	90                   	nop
  4025ac:	90                   	nop
  4025ad:	90                   	nop
  4025ae:	90                   	nop
  4025af:	90                   	nop

00000000004025b0 <__libc_csu_init>:
  4025b0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4025b5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4025ba:	48 8d 2d 63 18 20 00 	lea    0x201863(%rip),%rbp        # 603e24 <__init_array_end>
  4025c1:	4c 8d 25 5c 18 20 00 	lea    0x20185c(%rip),%r12        # 603e24 <__init_array_end>
  4025c8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4025cd:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  4025d2:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  4025d7:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  4025dc:	48 83 ec 38          	sub    $0x38,%rsp
  4025e0:	4c 29 e5             	sub    %r12,%rbp
  4025e3:	41 89 fd             	mov    %edi,%r13d
  4025e6:	49 89 f6             	mov    %rsi,%r14
  4025e9:	48 c1 fd 03          	sar    $0x3,%rbp
  4025ed:	49 89 d7             	mov    %rdx,%r15
  4025f0:	e8 43 e5 ff ff       	callq  400b38 <_init>
  4025f5:	48 85 ed             	test   %rbp,%rbp
  4025f8:	74 1c                	je     402616 <__libc_csu_init+0x66>
  4025fa:	31 db                	xor    %ebx,%ebx
  4025fc:	0f 1f 40 00          	nopl   0x0(%rax)
  402600:	4c 89 fa             	mov    %r15,%rdx
  402603:	4c 89 f6             	mov    %r14,%rsi
  402606:	44 89 ef             	mov    %r13d,%edi
  402609:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40260d:	48 83 c3 01          	add    $0x1,%rbx
  402611:	48 39 eb             	cmp    %rbp,%rbx
  402614:	75 ea                	jne    402600 <__libc_csu_init+0x50>
  402616:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40261b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  402620:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  402625:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40262a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40262f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  402634:	48 83 c4 38          	add    $0x38,%rsp
  402638:	c3                   	retq   
  402639:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000402640 <__libc_csu_fini>:
  402640:	f3 c3                	repz retq 
  402642:	90                   	nop
  402643:	90                   	nop
  402644:	90                   	nop
  402645:	90                   	nop
  402646:	90                   	nop
  402647:	90                   	nop
  402648:	90                   	nop
  402649:	90                   	nop
  40264a:	90                   	nop
  40264b:	90                   	nop
  40264c:	90                   	nop
  40264d:	90                   	nop
  40264e:	90                   	nop
  40264f:	90                   	nop

0000000000402650 <__do_global_ctors_aux>:
  402650:	55                   	push   %rbp
  402651:	48 89 e5             	mov    %rsp,%rbp
  402654:	53                   	push   %rbx
  402655:	48 83 ec 08          	sub    $0x8,%rsp
  402659:	48 8b 05 c8 17 20 00 	mov    0x2017c8(%rip),%rax        # 603e28 <__CTOR_LIST__>
  402660:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  402664:	74 19                	je     40267f <__do_global_ctors_aux+0x2f>
  402666:	bb 28 3e 60 00       	mov    $0x603e28,%ebx
  40266b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  402670:	48 83 eb 08          	sub    $0x8,%rbx
  402674:	ff d0                	callq  *%rax
  402676:	48 8b 03             	mov    (%rbx),%rax
  402679:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40267d:	75 f1                	jne    402670 <__do_global_ctors_aux+0x20>
  40267f:	48 83 c4 08          	add    $0x8,%rsp
  402683:	5b                   	pop    %rbx
  402684:	5d                   	pop    %rbp
  402685:	c3                   	retq   
  402686:	90                   	nop
  402687:	90                   	nop

Disassembly of section .fini:

0000000000402688 <_fini>:
  402688:	48 83 ec 08          	sub    $0x8,%rsp
  40268c:	e8 ef e6 ff ff       	callq  400d80 <__do_global_dtors_aux>
  402691:	48 83 c4 08          	add    $0x8,%rsp
  402695:	c3                   	retq   
