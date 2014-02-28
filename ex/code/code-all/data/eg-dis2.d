
eg-dis:     file format elf32-i386


Disassembly of section .init:

08048234 <_init>:
 8048234:	55                   	push   %ebp
 8048235:	89 e5                	mov    %esp,%ebp
 8048237:	53                   	push   %ebx
 8048238:	83 ec 04             	sub    $0x4,%esp
 804823b:	e8 00 00 00 00       	call   8048240 <_init+0xc>
 8048240:	5b                   	pop    %ebx
 8048241:	81 c3 24 13 00 00    	add    $0x1324,%ebx
 8048247:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 804824d:	85 d2                	test   %edx,%edx
 804824f:	74 05                	je     8048256 <_init+0x22>
 8048251:	e8 1e 00 00 00       	call   8048274 <__gmon_start__@plt>
 8048256:	e8 d5 00 00 00       	call   8048330 <frame_dummy>
 804825b:	e8 d0 01 00 00       	call   8048430 <__do_global_ctors_aux>
 8048260:	58                   	pop    %eax
 8048261:	5b                   	pop    %ebx
 8048262:	c9                   	leave  
 8048263:	c3                   	ret    

Disassembly of section .plt:

08048264 <__gmon_start__@plt-0x10>:
 8048264:	ff 35 68 95 04 08    	pushl  0x8049568
 804826a:	ff 25 6c 95 04 08    	jmp    *0x804956c
 8048270:	00 00                	add    %al,(%eax)
	...

08048274 <__gmon_start__@plt>:
 8048274:	ff 25 70 95 04 08    	jmp    *0x8049570
 804827a:	68 00 00 00 00       	push   $0x0
 804827f:	e9 e0 ff ff ff       	jmp    8048264 <_init+0x30>

08048284 <__libc_start_main@plt>:
 8048284:	ff 25 74 95 04 08    	jmp    *0x8049574
 804828a:	68 08 00 00 00       	push   $0x8
 804828f:	e9 d0 ff ff ff       	jmp    8048264 <_init+0x30>

Disassembly of section .text:

080482a0 <_start>:
 80482a0:	31 ed                	xor    %ebp,%ebp
 80482a2:	5e                   	pop    %esi
 80482a3:	89 e1                	mov    %esp,%ecx
 80482a5:	83 e4 f0             	and    $0xfffffff0,%esp
 80482a8:	50                   	push   %eax
 80482a9:	54                   	push   %esp
 80482aa:	52                   	push   %edx
 80482ab:	68 20 84 04 08       	push   $0x8048420
 80482b0:	68 c0 83 04 08       	push   $0x80483c0
 80482b5:	51                   	push   %ecx
 80482b6:	56                   	push   %esi
 80482b7:	68 a0 83 04 08       	push   $0x80483a0
 80482bc:	e8 c3 ff ff ff       	call   8048284 <__libc_start_main@plt>
 80482c1:	f4                   	hlt    
 80482c2:	90                   	nop
 80482c3:	90                   	nop
 80482c4:	90                   	nop
 80482c5:	90                   	nop
 80482c6:	90                   	nop
 80482c7:	90                   	nop
 80482c8:	90                   	nop
 80482c9:	90                   	nop
 80482ca:	90                   	nop
 80482cb:	90                   	nop
 80482cc:	90                   	nop
 80482cd:	90                   	nop
 80482ce:	90                   	nop
 80482cf:	90                   	nop

080482d0 <__do_global_dtors_aux>:
 80482d0:	55                   	push   %ebp
 80482d1:	89 e5                	mov    %esp,%ebp
 80482d3:	53                   	push   %ebx
 80482d4:	83 ec 04             	sub    $0x4,%esp
 80482d7:	80 3d 80 95 04 08 00 	cmpb   $0x0,0x8049580
 80482de:	75 3f                	jne    804831f <__do_global_dtors_aux+0x4f>
 80482e0:	a1 84 95 04 08       	mov    0x8049584,%eax
 80482e5:	bb 90 94 04 08       	mov    $0x8049490,%ebx
 80482ea:	81 eb 8c 94 04 08    	sub    $0x804948c,%ebx
 80482f0:	c1 fb 02             	sar    $0x2,%ebx
 80482f3:	83 eb 01             	sub    $0x1,%ebx
 80482f6:	39 d8                	cmp    %ebx,%eax
 80482f8:	73 1e                	jae    8048318 <__do_global_dtors_aux+0x48>
 80482fa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048300:	83 c0 01             	add    $0x1,%eax
 8048303:	a3 84 95 04 08       	mov    %eax,0x8049584
 8048308:	ff 14 85 8c 94 04 08 	call   *0x804948c(,%eax,4)
 804830f:	a1 84 95 04 08       	mov    0x8049584,%eax
 8048314:	39 d8                	cmp    %ebx,%eax
 8048316:	72 e8                	jb     8048300 <__do_global_dtors_aux+0x30>
 8048318:	c6 05 80 95 04 08 01 	movb   $0x1,0x8049580
 804831f:	83 c4 04             	add    $0x4,%esp
 8048322:	5b                   	pop    %ebx
 8048323:	5d                   	pop    %ebp
 8048324:	c3                   	ret    
 8048325:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048329:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048330 <frame_dummy>:
 8048330:	55                   	push   %ebp
 8048331:	89 e5                	mov    %esp,%ebp
 8048333:	83 ec 18             	sub    $0x18,%esp
 8048336:	a1 94 94 04 08       	mov    0x8049494,%eax
 804833b:	85 c0                	test   %eax,%eax
 804833d:	74 12                	je     8048351 <frame_dummy+0x21>
 804833f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048344:	85 c0                	test   %eax,%eax
 8048346:	74 09                	je     8048351 <frame_dummy+0x21>
 8048348:	c7 04 24 94 94 04 08 	movl   $0x8049494,(%esp)
 804834f:	ff d0                	call   *%eax
 8048351:	c9                   	leave  
 8048352:	c3                   	ret    
 8048353:	90                   	nop
 8048354:	90                   	nop
 8048355:	90                   	nop
 8048356:	90                   	nop
 8048357:	90                   	nop
 8048358:	90                   	nop
 8048359:	90                   	nop
 804835a:	90                   	nop
 804835b:	90                   	nop
 804835c:	90                   	nop
 804835d:	90                   	nop
 804835e:	90                   	nop
 804835f:	90                   	nop

08048360 <proca>:
 8048360:	55                   	push   %ebp
 8048361:	89 e5                	mov    %esp,%ebp
 8048363:	81 ec 90 01 00 00    	sub    $0x190,%esp
 8048369:	8b 45 08             	mov    0x8(%ebp),%eax
 804836c:	8b 95 d4 fe ff ff    	mov    -0x12c(%ebp),%edx
 8048372:	89 50 44             	mov    %edx,0x44(%eax)
 8048375:	8b 40 20             	mov    0x20(%eax),%eax
 8048378:	c9                   	leave  
 8048379:	c3                   	ret    
 804837a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08048380 <procb>:
 8048380:	55                   	push   %ebp
 8048381:	89 e5                	mov    %esp,%ebp
 8048383:	81 ec 70 01 00 00    	sub    $0x170,%esp
 8048389:	8b 45 08             	mov    0x8(%ebp),%eax
 804838c:	8b 95 10 ff ff ff    	mov    -0xf0(%ebp),%edx
 8048392:	89 50 1c             	mov    %edx,0x1c(%eax)
 8048395:	8b 40 18             	mov    0x18(%eax),%eax
 8048398:	c9                   	leave  
 8048399:	c3                   	ret    
 804839a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

080483a0 <main>:
 80483a0:	55                   	push   %ebp
 80483a1:	89 e5                	mov    %esp,%ebp
 80483a3:	83 ec 30             	sub    $0x30,%esp
 80483a6:	6a 07                	push   $0x7
 80483a8:	6a 05                	push   $0x5
 80483aa:	8d 45 d8             	lea    -0x28(%ebp),%eax
 80483ad:	50                   	push   %eax
 80483ae:	e8 ad ff ff ff       	call   8048360 <proca>
 80483b3:	c9                   	leave  
 80483b4:	c3                   	ret    
 80483b5:	90                   	nop
 80483b6:	90                   	nop
 80483b7:	90                   	nop
 80483b8:	90                   	nop
 80483b9:	90                   	nop
 80483ba:	90                   	nop
 80483bb:	90                   	nop
 80483bc:	90                   	nop
 80483bd:	90                   	nop
 80483be:	90                   	nop
 80483bf:	90                   	nop

080483c0 <__libc_csu_init>:
 80483c0:	55                   	push   %ebp
 80483c1:	89 e5                	mov    %esp,%ebp
 80483c3:	57                   	push   %edi
 80483c4:	56                   	push   %esi
 80483c5:	53                   	push   %ebx
 80483c6:	e8 5a 00 00 00       	call   8048425 <__i686.get_pc_thunk.bx>
 80483cb:	81 c3 99 11 00 00    	add    $0x1199,%ebx
 80483d1:	83 ec 1c             	sub    $0x1c,%esp
 80483d4:	e8 5b fe ff ff       	call   8048234 <_init>
 80483d9:	8d bb 20 ff ff ff    	lea    -0xe0(%ebx),%edi
 80483df:	8d 83 20 ff ff ff    	lea    -0xe0(%ebx),%eax
 80483e5:	29 c7                	sub    %eax,%edi
 80483e7:	c1 ff 02             	sar    $0x2,%edi
 80483ea:	85 ff                	test   %edi,%edi
 80483ec:	74 24                	je     8048412 <__libc_csu_init+0x52>
 80483ee:	31 f6                	xor    %esi,%esi
 80483f0:	8b 45 10             	mov    0x10(%ebp),%eax
 80483f3:	89 44 24 08          	mov    %eax,0x8(%esp)
 80483f7:	8b 45 0c             	mov    0xc(%ebp),%eax
 80483fa:	89 44 24 04          	mov    %eax,0x4(%esp)
 80483fe:	8b 45 08             	mov    0x8(%ebp),%eax
 8048401:	89 04 24             	mov    %eax,(%esp)
 8048404:	ff 94 b3 20 ff ff ff 	call   *-0xe0(%ebx,%esi,4)
 804840b:	83 c6 01             	add    $0x1,%esi
 804840e:	39 fe                	cmp    %edi,%esi
 8048410:	72 de                	jb     80483f0 <__libc_csu_init+0x30>
 8048412:	83 c4 1c             	add    $0x1c,%esp
 8048415:	5b                   	pop    %ebx
 8048416:	5e                   	pop    %esi
 8048417:	5f                   	pop    %edi
 8048418:	5d                   	pop    %ebp
 8048419:	c3                   	ret    
 804841a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

08048420 <__libc_csu_fini>:
 8048420:	55                   	push   %ebp
 8048421:	89 e5                	mov    %esp,%ebp
 8048423:	5d                   	pop    %ebp
 8048424:	c3                   	ret    

08048425 <__i686.get_pc_thunk.bx>:
 8048425:	8b 1c 24             	mov    (%esp),%ebx
 8048428:	c3                   	ret    
 8048429:	90                   	nop
 804842a:	90                   	nop
 804842b:	90                   	nop
 804842c:	90                   	nop
 804842d:	90                   	nop
 804842e:	90                   	nop
 804842f:	90                   	nop

08048430 <__do_global_ctors_aux>:
 8048430:	55                   	push   %ebp
 8048431:	89 e5                	mov    %esp,%ebp
 8048433:	53                   	push   %ebx
 8048434:	83 ec 04             	sub    $0x4,%esp
 8048437:	a1 84 94 04 08       	mov    0x8049484,%eax
 804843c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804843f:	74 13                	je     8048454 <__do_global_ctors_aux+0x24>
 8048441:	bb 84 94 04 08       	mov    $0x8049484,%ebx
 8048446:	66 90                	xchg   %ax,%ax
 8048448:	83 eb 04             	sub    $0x4,%ebx
 804844b:	ff d0                	call   *%eax
 804844d:	8b 03                	mov    (%ebx),%eax
 804844f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048452:	75 f4                	jne    8048448 <__do_global_ctors_aux+0x18>
 8048454:	83 c4 04             	add    $0x4,%esp
 8048457:	5b                   	pop    %ebx
 8048458:	5d                   	pop    %ebp
 8048459:	c3                   	ret    
 804845a:	90                   	nop
 804845b:	90                   	nop

Disassembly of section .fini:

0804845c <_fini>:
 804845c:	55                   	push   %ebp
 804845d:	89 e5                	mov    %esp,%ebp
 804845f:	53                   	push   %ebx
 8048460:	83 ec 04             	sub    $0x4,%esp
 8048463:	e8 00 00 00 00       	call   8048468 <_fini+0xc>
 8048468:	5b                   	pop    %ebx
 8048469:	81 c3 fc 10 00 00    	add    $0x10fc,%ebx
 804846f:	e8 5c fe ff ff       	call   80482d0 <__do_global_dtors_aux>
 8048474:	59                   	pop    %ecx
 8048475:	5b                   	pop    %ebx
 8048476:	c9                   	leave  
 8048477:	c3                   	ret    
