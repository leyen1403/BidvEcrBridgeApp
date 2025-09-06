# VI — Hướng dẫn triển khai DLL

## Mục tiêu

Sao chép các thư viện `.dll` đã build sang dự án cần dùng.

## Bước thực hiện

1. Mở Solution. Chọn cấu hình **Release**. Build.
2. Mở thư mục xuất bản:

   * C++ native: `.../<Project>/Release/` hoặc `.../<Project>/x64/Release/`
   * .NET: `.../<Project>/bin/Release/` hoặc `.../<Project>/bin/x64/Release/`
3. Sao chép **tất cả** file `*.dll` cần dùng.
4. Dán vào thư mục chạy của dự án đích (thường là cùng nơi chứa `.exe`).
5. Khởi động lại ứng dụng.

## Lưu ý

* Khớp kiến trúc CPU: `x86` với `x86`, `x64` với `x64`.
* Có thể cần **Microsoft Visual C++ 2015–2019 Redistributable** cho toolset v140.
* Khi ghi đè DLL đã tồn tại, kiểm tra phiên bản để tránh lỗi tương thích.

---

# EN — DLL Deployment Guide

## Goal

Copy built `.dll` libraries to the consuming project.

## Steps

1. Open the solution. Select **Release**. Build.
2. Open the output folder:

   * Native C++: `.../<Project>/Release/` or `.../<Project>/x64/Release/`
   * .NET: `.../<Project>/bin/Release/` or `.../<Project>/bin/x64/Release/`
3. Copy **all** required `*.dll` files.
4. Paste into the target project's runtime folder (usually next to the `.exe`).
5. Restart the application.

## Notes

* Match CPU architecture: `x86` to `x86`, `x64` to `x64`.
* **Microsoft Visual C++ 2015–2019 Redistributable** may be required for toolset v140.
* When overwriting existing DLLs, verify versions to avoid compatibility issues.

---

# KO — DLL 배포 안내

## 목적

빌드된 `.dll` 라이브러리를 사용하는 프로젝트에 복사.

## 절차

1. 솔루션을 연다. **Release** 구성으로 빌드.
2. 출력 폴더를 연다:

   * 네이티브 C++: `.../<Project>/Release/` 또는 `.../<Project>/x64/Release/`
   * .NET: `.../<Project>/bin/Release/` 또는 `.../<Project>/bin/x64/Release/`
3. 필요한 `*.dll` 파일을 모두 복사.
4. 대상 프로젝트 실행 폴더에 붙여넣기(보통 `.exe`와 동일 위치).
5. 애플리케이션 재시작.

## 참고

* CPU 아키텍처 일치 필요: `x86`↔`x86`, `x64`↔`x64`.
* v140 툴셋 사용 시 **Microsoft Visual C++ 2015–2019 재배포 패키지**가 필요할 수 있음.
* 기존 DLL을 덮어쓸 때 버전을 확인하여 호환성 문제를 방지.
