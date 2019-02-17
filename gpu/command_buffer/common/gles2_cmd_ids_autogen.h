// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is auto-generated from
// gpu/command_buffer/build_gles2_cmd_buffer.py
// It's formatted by clang-format using chromium coding style:
//    clang-format -i -style=chromium filename
// DO NOT EDIT!

#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_

#define GLES2_COMMAND_LIST(OP)                                       \
  OP(ActiveTexture)                                        /* 256 */ \
  OP(AttachShader)                                         /* 257 */ \
  OP(BindAttribLocationBucket)                             /* 258 */ \
  OP(BindBuffer)                                           /* 259 */ \
  OP(BindBufferBase)                                       /* 260 */ \
  OP(BindBufferRange)                                      /* 261 */ \
  OP(BindFramebuffer)                                      /* 262 */ \
  OP(BindRenderbuffer)                                     /* 263 */ \
  OP(BindSampler)                                          /* 264 */ \
  OP(BindTexture)                                          /* 265 */ \
  OP(BindTransformFeedback)                                /* 266 */ \
  OP(BlendColor)                                           /* 267 */ \
  OP(BlendEquation)                                        /* 268 */ \
  OP(BlendEquationSeparate)                                /* 269 */ \
  OP(BlendFunc)                                            /* 270 */ \
  OP(BlendFuncSeparate)                                    /* 271 */ \
  OP(BufferData)                                           /* 272 */ \
  OP(BufferSubData)                                        /* 273 */ \
  OP(CheckFramebufferStatus)                               /* 274 */ \
  OP(Clear)                                                /* 275 */ \
  OP(ClearBufferfi)                                        /* 276 */ \
  OP(ClearBufferfvImmediate)                               /* 277 */ \
  OP(ClearBufferivImmediate)                               /* 278 */ \
  OP(ClearBufferuivImmediate)                              /* 279 */ \
  OP(ClearColor)                                           /* 280 */ \
  OP(ClearDepthf)                                          /* 281 */ \
  OP(ClearStencil)                                         /* 282 */ \
  OP(ClientWaitSync)                                       /* 283 */ \
  OP(ColorMask)                                            /* 284 */ \
  OP(CompileShader)                                        /* 285 */ \
  OP(CompressedTexImage2DBucket)                           /* 286 */ \
  OP(CompressedTexImage2D)                                 /* 287 */ \
  OP(CompressedTexSubImage2DBucket)                        /* 288 */ \
  OP(CompressedTexSubImage2D)                              /* 289 */ \
  OP(CompressedTexImage3DBucket)                           /* 290 */ \
  OP(CompressedTexImage3D)                                 /* 291 */ \
  OP(CompressedTexSubImage3DBucket)                        /* 292 */ \
  OP(CompressedTexSubImage3D)                              /* 293 */ \
  OP(CopyBufferSubData)                                    /* 294 */ \
  OP(CopyTexImage2D)                                       /* 295 */ \
  OP(CopyTexSubImage2D)                                    /* 296 */ \
  OP(CopyTexSubImage3D)                                    /* 297 */ \
  OP(CreateProgram)                                        /* 298 */ \
  OP(CreateShader)                                         /* 299 */ \
  OP(CullFace)                                             /* 300 */ \
  OP(DeleteBuffersImmediate)                               /* 301 */ \
  OP(DeleteFramebuffersImmediate)                          /* 302 */ \
  OP(DeleteProgram)                                        /* 303 */ \
  OP(DeleteRenderbuffersImmediate)                         /* 304 */ \
  OP(DeleteSamplersImmediate)                              /* 305 */ \
  OP(DeleteSync)                                           /* 306 */ \
  OP(DeleteShader)                                         /* 307 */ \
  OP(DeleteTexturesImmediate)                              /* 308 */ \
  OP(DeleteTransformFeedbacksImmediate)                    /* 309 */ \
  OP(DepthFunc)                                            /* 310 */ \
  OP(DepthMask)                                            /* 311 */ \
  OP(DepthRangef)                                          /* 312 */ \
  OP(DetachShader)                                         /* 313 */ \
  OP(Disable)                                              /* 314 */ \
  OP(DisableVertexAttribArray)                             /* 315 */ \
  OP(DrawArrays)                                           /* 316 */ \
  OP(DrawElements)                                         /* 317 */ \
  OP(Enable)                                               /* 318 */ \
  OP(EnableVertexAttribArray)                              /* 319 */ \
  OP(FenceSync)                                            /* 320 */ \
  OP(Finish)                                               /* 321 */ \
  OP(Flush)                                                /* 322 */ \
  OP(FramebufferRenderbuffer)                              /* 323 */ \
  OP(FramebufferTexture2D)                                 /* 324 */ \
  OP(FramebufferTextureLayer)                              /* 325 */ \
  OP(FrontFace)                                            /* 326 */ \
  OP(GenBuffersImmediate)                                  /* 327 */ \
  OP(GenerateMipmap)                                       /* 328 */ \
  OP(GenFramebuffersImmediate)                             /* 329 */ \
  OP(GenRenderbuffersImmediate)                            /* 330 */ \
  OP(GenSamplersImmediate)                                 /* 331 */ \
  OP(GenTexturesImmediate)                                 /* 332 */ \
  OP(GenTransformFeedbacksImmediate)                       /* 333 */ \
  OP(GetActiveAttrib)                                      /* 334 */ \
  OP(GetActiveUniform)                                     /* 335 */ \
  OP(GetActiveUniformBlockiv)                              /* 336 */ \
  OP(GetActiveUniformBlockName)                            /* 337 */ \
  OP(GetActiveUniformsiv)                                  /* 338 */ \
  OP(GetAttachedShaders)                                   /* 339 */ \
  OP(GetAttribLocation)                                    /* 340 */ \
  OP(GetBooleanv)                                          /* 341 */ \
  OP(GetBufferParameteri64v)                               /* 342 */ \
  OP(GetBufferParameteriv)                                 /* 343 */ \
  OP(GetError)                                             /* 344 */ \
  OP(GetFloatv)                                            /* 345 */ \
  OP(GetFragDataLocation)                                  /* 346 */ \
  OP(GetFramebufferAttachmentParameteriv)                  /* 347 */ \
  OP(GetInteger64v)                                        /* 348 */ \
  OP(GetIntegeri_v)                                        /* 349 */ \
  OP(GetInteger64i_v)                                      /* 350 */ \
  OP(GetIntegerv)                                          /* 351 */ \
  OP(GetInternalformativ)                                  /* 352 */ \
  OP(GetProgramiv)                                         /* 353 */ \
  OP(GetProgramInfoLog)                                    /* 354 */ \
  OP(GetRenderbufferParameteriv)                           /* 355 */ \
  OP(GetSamplerParameterfv)                                /* 356 */ \
  OP(GetSamplerParameteriv)                                /* 357 */ \
  OP(GetShaderiv)                                          /* 358 */ \
  OP(GetShaderInfoLog)                                     /* 359 */ \
  OP(GetShaderPrecisionFormat)                             /* 360 */ \
  OP(GetShaderSource)                                      /* 361 */ \
  OP(GetString)                                            /* 362 */ \
  OP(GetSynciv)                                            /* 363 */ \
  OP(GetTexParameterfv)                                    /* 364 */ \
  OP(GetTexParameteriv)                                    /* 365 */ \
  OP(GetTransformFeedbackVarying)                          /* 366 */ \
  OP(GetUniformBlockIndex)                                 /* 367 */ \
  OP(GetUniformfv)                                         /* 368 */ \
  OP(GetUniformiv)                                         /* 369 */ \
  OP(GetUniformuiv)                                        /* 370 */ \
  OP(GetUniformIndices)                                    /* 371 */ \
  OP(GetUniformLocation)                                   /* 372 */ \
  OP(GetVertexAttribfv)                                    /* 373 */ \
  OP(GetVertexAttribiv)                                    /* 374 */ \
  OP(GetVertexAttribIiv)                                   /* 375 */ \
  OP(GetVertexAttribIuiv)                                  /* 376 */ \
  OP(GetVertexAttribPointerv)                              /* 377 */ \
  OP(Hint)                                                 /* 378 */ \
  OP(InvalidateFramebufferImmediate)                       /* 379 */ \
  OP(InvalidateSubFramebufferImmediate)                    /* 380 */ \
  OP(IsBuffer)                                             /* 381 */ \
  OP(IsEnabled)                                            /* 382 */ \
  OP(IsFramebuffer)                                        /* 383 */ \
  OP(IsProgram)                                            /* 384 */ \
  OP(IsRenderbuffer)                                       /* 385 */ \
  OP(IsSampler)                                            /* 386 */ \
  OP(IsShader)                                             /* 387 */ \
  OP(IsSync)                                               /* 388 */ \
  OP(IsTexture)                                            /* 389 */ \
  OP(IsTransformFeedback)                                  /* 390 */ \
  OP(LineWidth)                                            /* 391 */ \
  OP(LinkProgram)                                          /* 392 */ \
  OP(PauseTransformFeedback)                               /* 393 */ \
  OP(PixelStorei)                                          /* 394 */ \
  OP(PolygonOffset)                                        /* 395 */ \
  OP(ReadBuffer)                                           /* 396 */ \
  OP(ReadPixels)                                           /* 397 */ \
  OP(ReleaseShaderCompiler)                                /* 398 */ \
  OP(RenderbufferStorage)                                  /* 399 */ \
  OP(ResumeTransformFeedback)                              /* 400 */ \
  OP(SampleCoverage)                                       /* 401 */ \
  OP(SamplerParameterf)                                    /* 402 */ \
  OP(SamplerParameterfvImmediate)                          /* 403 */ \
  OP(SamplerParameteri)                                    /* 404 */ \
  OP(SamplerParameterivImmediate)                          /* 405 */ \
  OP(Scissor)                                              /* 406 */ \
  OP(ShaderBinary)                                         /* 407 */ \
  OP(ShaderSourceBucket)                                   /* 408 */ \
  OP(MultiDrawBeginCHROMIUM)                               /* 409 */ \
  OP(MultiDrawEndCHROMIUM)                                 /* 410 */ \
  OP(MultiDrawArraysCHROMIUM)                              /* 411 */ \
  OP(MultiDrawArraysInstancedCHROMIUM)                     /* 412 */ \
  OP(MultiDrawElementsCHROMIUM)                            /* 413 */ \
  OP(MultiDrawElementsInstancedCHROMIUM)                   /* 414 */ \
  OP(StencilFunc)                                          /* 415 */ \
  OP(StencilFuncSeparate)                                  /* 416 */ \
  OP(StencilMask)                                          /* 417 */ \
  OP(StencilMaskSeparate)                                  /* 418 */ \
  OP(StencilOp)                                            /* 419 */ \
  OP(StencilOpSeparate)                                    /* 420 */ \
  OP(TexImage2D)                                           /* 421 */ \
  OP(TexImage3D)                                           /* 422 */ \
  OP(TexParameterf)                                        /* 423 */ \
  OP(TexParameterfvImmediate)                              /* 424 */ \
  OP(TexParameteri)                                        /* 425 */ \
  OP(TexParameterivImmediate)                              /* 426 */ \
  OP(TexStorage3D)                                         /* 427 */ \
  OP(TexSubImage2D)                                        /* 428 */ \
  OP(TexSubImage3D)                                        /* 429 */ \
  OP(TransformFeedbackVaryingsBucket)                      /* 430 */ \
  OP(Uniform1f)                                            /* 431 */ \
  OP(Uniform1fvImmediate)                                  /* 432 */ \
  OP(Uniform1i)                                            /* 433 */ \
  OP(Uniform1ivImmediate)                                  /* 434 */ \
  OP(Uniform1ui)                                           /* 435 */ \
  OP(Uniform1uivImmediate)                                 /* 436 */ \
  OP(Uniform2f)                                            /* 437 */ \
  OP(Uniform2fvImmediate)                                  /* 438 */ \
  OP(Uniform2i)                                            /* 439 */ \
  OP(Uniform2ivImmediate)                                  /* 440 */ \
  OP(Uniform2ui)                                           /* 441 */ \
  OP(Uniform2uivImmediate)                                 /* 442 */ \
  OP(Uniform3f)                                            /* 443 */ \
  OP(Uniform3fvImmediate)                                  /* 444 */ \
  OP(Uniform3i)                                            /* 445 */ \
  OP(Uniform3ivImmediate)                                  /* 446 */ \
  OP(Uniform3ui)                                           /* 447 */ \
  OP(Uniform3uivImmediate)                                 /* 448 */ \
  OP(Uniform4f)                                            /* 449 */ \
  OP(Uniform4fvImmediate)                                  /* 450 */ \
  OP(Uniform4i)                                            /* 451 */ \
  OP(Uniform4ivImmediate)                                  /* 452 */ \
  OP(Uniform4ui)                                           /* 453 */ \
  OP(Uniform4uivImmediate)                                 /* 454 */ \
  OP(UniformBlockBinding)                                  /* 455 */ \
  OP(UniformMatrix2fvImmediate)                            /* 456 */ \
  OP(UniformMatrix2x3fvImmediate)                          /* 457 */ \
  OP(UniformMatrix2x4fvImmediate)                          /* 458 */ \
  OP(UniformMatrix3fvImmediate)                            /* 459 */ \
  OP(UniformMatrix3x2fvImmediate)                          /* 460 */ \
  OP(UniformMatrix3x4fvImmediate)                          /* 461 */ \
  OP(UniformMatrix4fvImmediate)                            /* 462 */ \
  OP(UniformMatrix4x2fvImmediate)                          /* 463 */ \
  OP(UniformMatrix4x3fvImmediate)                          /* 464 */ \
  OP(UseProgram)                                           /* 465 */ \
  OP(ValidateProgram)                                      /* 466 */ \
  OP(VertexAttrib1f)                                       /* 467 */ \
  OP(VertexAttrib1fvImmediate)                             /* 468 */ \
  OP(VertexAttrib2f)                                       /* 469 */ \
  OP(VertexAttrib2fvImmediate)                             /* 470 */ \
  OP(VertexAttrib3f)                                       /* 471 */ \
  OP(VertexAttrib3fvImmediate)                             /* 472 */ \
  OP(VertexAttrib4f)                                       /* 473 */ \
  OP(VertexAttrib4fvImmediate)                             /* 474 */ \
  OP(VertexAttribI4i)                                      /* 475 */ \
  OP(VertexAttribI4ivImmediate)                            /* 476 */ \
  OP(VertexAttribI4ui)                                     /* 477 */ \
  OP(VertexAttribI4uivImmediate)                           /* 478 */ \
  OP(VertexAttribIPointer)                                 /* 479 */ \
  OP(VertexAttribPointer)                                  /* 480 */ \
  OP(Viewport)                                             /* 481 */ \
  OP(WaitSync)                                             /* 482 */ \
  OP(BlitFramebufferCHROMIUM)                              /* 483 */ \
  OP(RenderbufferStorageMultisampleCHROMIUM)               /* 484 */ \
  OP(RenderbufferStorageMultisampleAdvancedAMD)            /* 485 */ \
  OP(RenderbufferStorageMultisampleEXT)                    /* 486 */ \
  OP(FramebufferTexture2DMultisampleEXT)                   /* 487 */ \
  OP(TexStorage2DEXT)                                      /* 488 */ \
  OP(GenQueriesEXTImmediate)                               /* 489 */ \
  OP(DeleteQueriesEXTImmediate)                            /* 490 */ \
  OP(QueryCounterEXT)                                      /* 491 */ \
  OP(BeginQueryEXT)                                        /* 492 */ \
  OP(BeginTransformFeedback)                               /* 493 */ \
  OP(EndQueryEXT)                                          /* 494 */ \
  OP(EndTransformFeedback)                                 /* 495 */ \
  OP(SetDisjointValueSyncCHROMIUM)                         /* 496 */ \
  OP(InsertEventMarkerEXT)                                 /* 497 */ \
  OP(PushGroupMarkerEXT)                                   /* 498 */ \
  OP(PopGroupMarkerEXT)                                    /* 499 */ \
  OP(GenVertexArraysOESImmediate)                          /* 500 */ \
  OP(DeleteVertexArraysOESImmediate)                       /* 501 */ \
  OP(IsVertexArrayOES)                                     /* 502 */ \
  OP(BindVertexArrayOES)                                   /* 503 */ \
  OP(FramebufferParameteri)                                /* 504 */ \
  OP(BindImageTexture)                                     /* 505 */ \
  OP(DispatchCompute)                                      /* 506 */ \
  OP(GetProgramInterfaceiv)                                /* 507 */ \
  OP(GetProgramResourceIndex)                              /* 508 */ \
  OP(GetProgramResourceName)                               /* 509 */ \
  OP(GetProgramResourceiv)                                 /* 510 */ \
  OP(GetProgramResourceLocation)                           /* 511 */ \
  OP(MemoryBarrierEXT)                                     /* 512 */ \
  OP(MemoryBarrierByRegion)                                /* 513 */ \
  OP(SwapBuffers)                                          /* 514 */ \
  OP(GetMaxValueInBufferCHROMIUM)                          /* 515 */ \
  OP(EnableFeatureCHROMIUM)                                /* 516 */ \
  OP(MapBufferRange)                                       /* 517 */ \
  OP(UnmapBuffer)                                          /* 518 */ \
  OP(FlushMappedBufferRange)                               /* 519 */ \
  OP(ResizeCHROMIUM)                                       /* 520 */ \
  OP(GetRequestableExtensionsCHROMIUM)                     /* 521 */ \
  OP(RequestExtensionCHROMIUM)                             /* 522 */ \
  OP(GetProgramInfoCHROMIUM)                               /* 523 */ \
  OP(GetUniformBlocksCHROMIUM)                             /* 524 */ \
  OP(GetTransformFeedbackVaryingsCHROMIUM)                 /* 525 */ \
  OP(GetUniformsES3CHROMIUM)                               /* 526 */ \
  OP(DescheduleUntilFinishedCHROMIUM)                      /* 527 */ \
  OP(GetTranslatedShaderSourceANGLE)                       /* 528 */ \
  OP(PostSubBufferCHROMIUM)                                /* 529 */ \
  OP(CopyTextureCHROMIUM)                                  /* 530 */ \
  OP(CopySubTextureCHROMIUM)                               /* 531 */ \
  OP(DrawArraysInstancedANGLE)                             /* 532 */ \
  OP(DrawElementsInstancedANGLE)                           /* 533 */ \
  OP(VertexAttribDivisorANGLE)                             /* 534 */ \
  OP(ProduceTextureDirectCHROMIUMImmediate)                /* 535 */ \
  OP(CreateAndConsumeTextureINTERNALImmediate)             /* 536 */ \
  OP(BindUniformLocationCHROMIUMBucket)                    /* 537 */ \
  OP(BindTexImage2DCHROMIUM)                               /* 538 */ \
  OP(BindTexImage2DWithInternalformatCHROMIUM)             /* 539 */ \
  OP(ReleaseTexImage2DCHROMIUM)                            /* 540 */ \
  OP(TraceBeginCHROMIUM)                                   /* 541 */ \
  OP(TraceEndCHROMIUM)                                     /* 542 */ \
  OP(DiscardFramebufferEXTImmediate)                       /* 543 */ \
  OP(LoseContextCHROMIUM)                                  /* 544 */ \
  OP(InsertFenceSyncCHROMIUM)                              /* 545 */ \
  OP(UnpremultiplyAndDitherCopyCHROMIUM)                   /* 546 */ \
  OP(DrawBuffersEXTImmediate)                              /* 547 */ \
  OP(DiscardBackbufferCHROMIUM)                            /* 548 */ \
  OP(ScheduleOverlayPlaneCHROMIUM)                         /* 549 */ \
  OP(ScheduleCALayerSharedStateCHROMIUM)                   /* 550 */ \
  OP(ScheduleCALayerCHROMIUM)                              /* 551 */ \
  OP(ScheduleCALayerInUseQueryCHROMIUMImmediate)           /* 552 */ \
  OP(CommitOverlayPlanesCHROMIUM)                          /* 553 */ \
  OP(FlushDriverCachesCHROMIUM)                            /* 554 */ \
  OP(ScheduleDCLayerCHROMIUM)                              /* 555 */ \
  OP(SetActiveURLCHROMIUM)                                 /* 556 */ \
  OP(MatrixLoadfCHROMIUMImmediate)                         /* 557 */ \
  OP(MatrixLoadIdentityCHROMIUM)                           /* 558 */ \
  OP(GenPathsCHROMIUM)                                     /* 559 */ \
  OP(DeletePathsCHROMIUM)                                  /* 560 */ \
  OP(IsPathCHROMIUM)                                       /* 561 */ \
  OP(PathCommandsCHROMIUM)                                 /* 562 */ \
  OP(PathParameterfCHROMIUM)                               /* 563 */ \
  OP(PathParameteriCHROMIUM)                               /* 564 */ \
  OP(PathStencilFuncCHROMIUM)                              /* 565 */ \
  OP(StencilFillPathCHROMIUM)                              /* 566 */ \
  OP(StencilStrokePathCHROMIUM)                            /* 567 */ \
  OP(CoverFillPathCHROMIUM)                                /* 568 */ \
  OP(CoverStrokePathCHROMIUM)                              /* 569 */ \
  OP(StencilThenCoverFillPathCHROMIUM)                     /* 570 */ \
  OP(StencilThenCoverStrokePathCHROMIUM)                   /* 571 */ \
  OP(StencilFillPathInstancedCHROMIUM)                     /* 572 */ \
  OP(StencilStrokePathInstancedCHROMIUM)                   /* 573 */ \
  OP(CoverFillPathInstancedCHROMIUM)                       /* 574 */ \
  OP(CoverStrokePathInstancedCHROMIUM)                     /* 575 */ \
  OP(StencilThenCoverFillPathInstancedCHROMIUM)            /* 576 */ \
  OP(StencilThenCoverStrokePathInstancedCHROMIUM)          /* 577 */ \
  OP(BindFragmentInputLocationCHROMIUMBucket)              /* 578 */ \
  OP(ProgramPathFragmentInputGenCHROMIUM)                  /* 579 */ \
  OP(CoverageModulationCHROMIUM)                           /* 580 */ \
  OP(BlendBarrierKHR)                                      /* 581 */ \
  OP(ApplyScreenSpaceAntialiasingCHROMIUM)                 /* 582 */ \
  OP(BindFragDataLocationIndexedEXTBucket)                 /* 583 */ \
  OP(BindFragDataLocationEXTBucket)                        /* 584 */ \
  OP(GetFragDataIndexEXT)                                  /* 585 */ \
  OP(UniformMatrix4fvStreamTextureMatrixCHROMIUMImmediate) /* 586 */ \
  OP(OverlayPromotionHintCHROMIUM)                         /* 587 */ \
  OP(SwapBuffersWithBoundsCHROMIUMImmediate)               /* 588 */ \
  OP(SetDrawRectangleCHROMIUM)                             /* 589 */ \
  OP(SetEnableDCLayersCHROMIUM)                            /* 590 */ \
  OP(InitializeDiscardableTextureCHROMIUM)                 /* 591 */ \
  OP(UnlockDiscardableTextureCHROMIUM)                     /* 592 */ \
  OP(LockDiscardableTextureCHROMIUM)                       /* 593 */ \
  OP(TexStorage2DImageCHROMIUM)                            /* 594 */ \
  OP(SetColorSpaceMetadataCHROMIUM)                        /* 595 */ \
  OP(WindowRectanglesEXTImmediate)                         /* 596 */ \
  OP(CreateGpuFenceINTERNAL)                               /* 597 */ \
  OP(WaitGpuFenceCHROMIUM)                                 /* 598 */ \
  OP(DestroyGpuFenceCHROMIUM)                              /* 599 */ \
  OP(SetReadbackBufferShadowAllocationINTERNAL)            /* 600 */ \
  OP(FramebufferTextureMultiviewLayeredANGLE)              /* 601 */ \
  OP(MaxShaderCompilerThreadsKHR)                          /* 602 */ \
  OP(CreateAndTexStorage2DSharedImageINTERNALImmediate)    /* 603 */ \
  OP(BeginSharedImageAccessDirectCHROMIUM)                 /* 604 */ \
  OP(EndSharedImageAccessDirectCHROMIUM)                   /* 605 */

enum CommandId {
  kOneBeforeStartPoint =
      cmd::kLastCommonId,  // All GLES2 commands start after this.
#define GLES2_CMD_OP(name) k##name,
  GLES2_COMMAND_LIST(GLES2_CMD_OP)
#undef GLES2_CMD_OP
      kNumCommands,
  kFirstGLES2Command = kOneBeforeStartPoint + 1
};

#endif  // GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_